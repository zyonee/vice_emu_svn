/*
 * digimax.h
 *
 * Written by
 *  Marco van den Heuvel <viceteam@t-online.de>
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

#ifndef VICE_DIGIMAX_H
#define VICE_DIGIMAX_H

#include "types.h"
#include "sound.h"

extern int digimax_address;
extern int digimax_cart_enabled(void);
extern int digimax_enable(void);
extern void digimax_detach(void);
extern void digimax_reset(void);

extern int digimax_resources_init(void);
extern void digimax_resources_shutdown(void);
extern int digimax_cmdline_options_init(void);

extern void digimax_userport_store(WORD addr, BYTE value);

extern void digimax_sound_chip_init(void);

struct snapshot_s;

extern int digimax_snapshot_write_module(struct snapshot_s *s);
extern int digimax_snapshot_read_module(struct snapshot_s *s);

#endif
