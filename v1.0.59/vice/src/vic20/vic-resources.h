/*
 * vic-resources.h - Resource handling for the VIC-I emulation.
 *
 * Written by
 *  Ettore Perazzoli (ettore@comm2000.it)
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

#ifndef _VIC_RESOURCES_H
#define _VIC_RESOURCES_H

#include "vice.h"

struct _vic_resources
  {
    /* Flag: Do we use double size?  */
    int double_size_enabled;

    /* Flag: Do we enable the video cache?  */
    int video_cache_enabled;

    /* Flag: Do we copy lines in double size mode?  */
    int double_scan_enabled;

    /* Name of palette file.  */
    char *palette_file_name;

#ifdef USE_VIDMODE_EXTENSION
    /* Flag: Fullscreenmode?  */
    int fullscreen;

    /* Flag: Do we use double size?  */
    int fullscreen_double_size_enabled;

    /* Flag: Do we copy lines in double size mode?  */
    int fullscreen_double_scan_enabled;

    int fullscreen_width;
    int fullscreen_height;
#endif
  };
typedef struct _vic_resources vic_resources_t;

extern vic_resources_t vic_resources;



int vic_resources_init (void);

#endif
