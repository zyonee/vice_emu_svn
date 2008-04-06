/*
 * iecdrive.c - IEC bus handling for true drive emulaton.
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
 *  Daniel Sladic <sladic@eecg.toronto.edu>
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Andr� Fachat <fachat@physik.tu-chemnitz.de>
 *  Teemu Rantanen <tvr@cs.hut.fi>
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


#ifndef _IECDRIVE_H
#define _IECDRIVE_H

#include "types.h"

extern void iec_update_ports_embedded(void);
extern void iec_drive0_write(BYTE data);
extern void iec_drive1_write(BYTE data);
extern BYTE iec_drive0_read(void);
extern BYTE iec_drive1_read(void);
extern void iec_fast_drive_write(BYTE data, unsigned int dnr);
extern void iec_fast_cpu_write(BYTE data);
extern void iec_fast_drive_direction(int direction, unsigned int dnr);
extern void iec_fast_cpu_direction(int direction);
extern void parallel_cable_drive0_write(BYTE data, int handshake);
extern void parallel_cable_drive1_write(BYTE data, int handshake);
extern BYTE parallel_cable_drive_read(int handshake);

extern void iec_update_cpu_bus(BYTE data);
extern void iec_update_ports(void);

/* return value for iec_available_busses() (can be ored) */
#define IEC_BUS_IEC     0x01    /* serial IEC bus */
#define IEC_BUS_IEEE    0x02    /* parallel IEEE bus */

extern int iec_available_busses(void);

extern void plus4tcbm_update_pa(BYTE byte, unsigned int dnr);
extern void plus4tcbm_update_pb(BYTE byte, unsigned int dnr);
extern void plus4tcbm_update_pc(BYTE byte, unsigned int dnr);
extern BYTE plus4tcbm_outputa[2], plus4tcbm_outputb[2], plus4tcbm_outputc[2];

#endif

