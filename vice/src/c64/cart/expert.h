/*
 * expert.h - Cartridge handling, Expert cart.
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

#ifndef VICE_EXPERT_H
#define VICE_EXPERT_H

#include <stdio.h>

#include "types.h"

extern BYTE REGPARM1 expert_roml_read(WORD addr);
extern void REGPARM2 expert_roml_store(WORD addr, BYTE value);
extern BYTE REGPARM1 expert_romh_read(WORD addr);

extern void expert_ack_reset(void);
extern void expert_ack_nmi(void);
extern void expert_freeze(void);

extern void expert_config_init(void);
extern void expert_config_setup(BYTE *rawcart);
extern int expert_bin_attach(const char *filename, BYTE *rawcart);
extern int expert_crt_attach(FILE *fd, BYTE *rawcart);
extern void expert_detach(void);

extern int expert_freeze_allowed(void);

extern void expert_mode_changed(int mode);

/* Expert cartridge has three modes: */
#define EXPERT_MODE_OFF                      0
#define EXPERT_MODE_PRG                      1
#define EXPERT_MODE_ON                       2

#endif
