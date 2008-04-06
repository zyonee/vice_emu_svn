/*
 * vdrive-bam.h - Virtual disk-drive implementation.
 *                BAM specific functions.
 *
 * Written by
 *  Andreas Boose       <boose@linux.rz.fh-hannover.de>
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

#ifndef _VDRIVE_BAM_H
#define _VDRIVE_BAM_H

#include "vdrive.h"

#define BAM_FIRST_TRACK         0
#define BAM_FIRST_SECTOR        1
#define BAM_FORMAT_TYPE         2
#define BAM_BIT_MAP             4       /* start of bitmap in each BAM blk */
#define BAM_BIT_MAP_1581        16
#define BAM_BIT_MAP_8050        6
#define BAM_BIT_MAP_8250        BAM_BIT_MAP_8050
#define BAM_VERSION_1541        165     /* position of DOS version (2A/2C)
                                           in BAM blk */
#define BAM_VERSION_1581        25
#define BAM_VERSION_8050        27
#define BAM_VERSION_8250        BAM_VERSION_8050

extern int vdrive_bam_allocate_chain(DRIVE *floppy, int t, int s);
extern int vdrive_bam_alloc_first_free_sector(DRIVE *floppy, BYTE *bam,
                                              int *track, int *sector);
extern int vdrive_bam_alloc_next_free_sector(DRIVE *floppy, BYTE *bam,
                                             int *track, int *sector);
extern int vdrive_bam_allocate_sector(int type, BYTE *bam, int track,
                                      int sector);
extern void vdrive_bam_clear_all(int type, BYTE *bam);
extern void vdrive_bam_create_empty_bam(DRIVE *floppy, const char *name,
                                        BYTE *id);
extern int vdrive_bam_free_block_count(DRIVE *floppy);
extern int vdrive_bam_free_sector(int type, BYTE *bam, int track, int sector);
extern int vdrive_bam_get_disk_id(DRIVE *floppy, BYTE *id);
extern int vdrive_bam_set_disk_id(DRIVE *floppy, BYTE *id);
extern int vdrive_bam_read_bam(DRIVE *floppy);
extern int vdrive_bam_write_bam(DRIVE *floppy);

#endif

