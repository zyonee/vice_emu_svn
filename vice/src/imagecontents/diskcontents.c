/*
 * diskcontents.c - Extract the directory from disk images.
 *
 * Written by
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Andreas Boose <viceteam@t-online.de>
 *  Tibor Biczo <crown@mail.matav.hu>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#include <stdio.h>
#include <string.h>

#include "diskimage.h"
#include "imagecontents.h"
#include "utils.h"
#include "types.h"
#include "vdrive-bam.h"
#include "vdrive-dir.h"
#include "vdrive-internal.h"
#include "vdrive.h"


/* Argh!  Really ugly!  FIXME!  */
extern char const *slot_type[];

/* This code is used to check whether the directory is circular.  It should
   be replaced by a more simple check that just stops if the number of
   entries is bigger than expected, but this needs some support in `vdrive.c'
   which we do not have yet.  */

static struct block_list_t {
    unsigned int track;
    unsigned int sector;
} *block_list = NULL;

unsigned int block_list_nelems;
unsigned int block_list_size;

static void circular_check_init(void)
{
    block_list_nelems = 0;
}

static int circular_check(unsigned int track, unsigned int sector)
{
    unsigned int i;

    for (i = 0; i < block_list_nelems; i++)
        if (block_list[i].track == track && block_list[i].sector == sector)
            return 1;

    if (block_list_nelems == block_list_size) {
        if (block_list_size == 0) {
            block_list_size = 512;
            block_list = xmalloc(sizeof(*block_list) * block_list_size);
        } else {
            block_list_size *= 2;
            block_list = xrealloc(block_list,
                                  sizeof(*block_list) * block_list_size);
        }
    }

    block_list[block_list_nelems].track = track;
    block_list[block_list_nelems++].sector = sector;

    return 0;
}

image_contents_t *diskcontents_read(const char *file_name, unsigned int unit)
{
    image_contents_t *new;
    vdrive_t *vdrive;
    BYTE buffer[256];
    int retval;
    image_contents_file_list_t *lp;

    vdrive = vdrive_internal_open_disk_image(file_name, unit, 1);

    if (vdrive == NULL)
        return NULL;

    retval = vdrive_bam_read_bam(vdrive);

    if (retval < 0) {
        vdrive_internal_close_disk_image(vdrive);
        return NULL;
    }

    new = image_contents_new();

    memcpy(new->name, vdrive->bam + vdrive->bam_name, IMAGE_CONTENTS_NAME_LEN);
    new->name[IMAGE_CONTENTS_NAME_LEN] = 0;

    memcpy(new->id, vdrive->bam + vdrive->bam_id, IMAGE_CONTENTS_ID_LEN);
    new->id[IMAGE_CONTENTS_ID_LEN] = 0;

    new->blocks_free = (int)vdrive_bam_free_block_count(vdrive);

    vdrive->Curr_track = vdrive->Dir_Track;
    vdrive->Curr_sector = vdrive->Dir_Sector;

    lp = NULL;
    new->file_list = NULL;

    circular_check_init();

    while (1) {
        BYTE *p;
        int j;

        retval = disk_image_read_sector(vdrive->image, buffer,
                                        vdrive->Curr_track,
                                        vdrive->Curr_sector);

        if (retval != 0
            || circular_check(vdrive->Curr_track, vdrive->Curr_sector)) {
            image_contents_destroy(new);
            vdrive_internal_close_disk_image(vdrive);
            return NULL;
        }

        for (p = buffer, j = 0; j < 8; j++, p += 32)
            if (p[SLOT_TYPE_OFFSET] != 0) {
                image_contents_file_list_t *new_list;
                int i;

                new_list = (image_contents_file_list_t*)xmalloc(
                           sizeof(image_contents_file_list_t));
                new_list->size = ((int) p[SLOT_NR_BLOCKS]
                                  + ((int) p[SLOT_NR_BLOCKS + 1] << 8));

                for (i = 0; i < IMAGE_CONTENTS_FILE_NAME_LEN; i++)
                        new_list->name[i] = p[SLOT_NAME_OFFSET + i];

                new_list->name[IMAGE_CONTENTS_FILE_NAME_LEN] = 0;

                new_list->name[i] = 0;

                sprintf((char *)new_list->type, "%c%s%c",
                        (p[SLOT_TYPE_OFFSET] & FT_CLOSED ? ' ' : '*'),
                        slot_type[p[SLOT_TYPE_OFFSET] & 0x07],
                        (p[SLOT_TYPE_OFFSET] & FT_LOCKED ? '<' : ' '));

                new_list->next = NULL;

                if (lp == NULL) {
                    new_list->prev = NULL;
                    new->file_list = new_list;
                    lp = new->file_list;
                } else {
                    new_list->prev = lp;
                    lp->next = new_list;
                    lp = new_list;
                }
            }

        if (buffer[0] == 0)
            break;

        vdrive->Curr_track = (int)buffer[0];
        vdrive->Curr_sector = (int)buffer[1];
    }

    vdrive_internal_close_disk_image(vdrive);
    return new;
}

char *diskcontents_filename_by_number(const char *filename, unsigned int unit,
                                      unsigned int file_index)
{
    image_contents_t *contents;
    image_contents_file_list_t *current;
    char *s;

    contents = diskcontents_read(filename, unit);

    if (contents == NULL)
        return NULL;

    s = NULL;

    if (file_index != 0) {
        current = contents->file_list;
        file_index--;
        while ((file_index != 0) && (current != NULL)) {
            current = current->next;
            file_index--;
        }
        if (current != NULL) {
            s = stralloc((char *)(current->name));
        }
    }

    image_contents_destroy(contents);

    return s;
}

