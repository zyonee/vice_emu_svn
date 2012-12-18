/*
 * scpu64mem.h -- Emulation of the main 65816 processor.
 *
 * Written by
 *  Kajtar Zsolt <soci@c64.rulez.org>
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

#ifndef VICE_SCPU64CPU_H
#define VICE_SCPU64CPU_H

int scpu64_get_half_cycle(void);
void scpu64_set_fastmode(int mode);
int scpu64_get_fastmode(void);
void scpu64_clock_read_stretch(void);
void scpu64_clock_readwrite_stretch_eprom(void);
void scpu64_clock_write_stretch(void);
void scpu64_clock_write_stretch_io(void);
void scpu64_clock_write_stretch_io_slow(void);
extern int scpu64_emulation_mode;

#endif
