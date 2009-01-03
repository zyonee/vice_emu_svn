/*
 * generic.h - Cartridge handling, generic carts.
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
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

#ifndef _GENERIC_H
#define _GENERIC_H

#include <stdio.h>

#include "types.h"

extern void generic_8kb_config_init(void);
extern void generic_16kb_config_init(void);
extern void generic_ultimax_config_init(void);
extern void generic_8kb_config_setup(BYTE *rawcart);
extern void generic_16kb_config_setup(BYTE *rawcart);
extern void generic_ultimax_config_setup(BYTE *rawcart);
extern int generic_8kb_bin_attach(const char *filename, BYTE *rawcart);
extern int generic_16kb_bin_attach(const char *filename, BYTE *rawcart);
extern int generic_crt_attach(FILE *fd, BYTE *rawcart);
extern void generic_8kb_detach(void);
extern void generic_16kb_detach(void);
extern void generic_ultimax_detach(void);

#endif

