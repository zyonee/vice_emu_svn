//  ---------------------------------------------------------------------------
//  This file is part of reSID, a MOS6581 SID emulator engine.
//  Copyright (C) 2004  Dag Lem <resid@nimrod.no>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//  ---------------------------------------------------------------------------

#include "wave.h"

reg8 WaveformGenerator::wave8580_P_T[] =
{
/* 0x000: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x008: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x010: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x018: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x020: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x028: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x030: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x038: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x040: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x048: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x050: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x058: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x060: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x068: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x070: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x078: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x080: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x088: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x090: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x098: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0a0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0a8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0b0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0b8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0c0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0c8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0d0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0d8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0e0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0e8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0f0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x0f8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
/* 0x100: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x108: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x110: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x118: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x120: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x128: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x130: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x138: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x140: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x148: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x150: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x158: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x160: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x168: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x170: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x178: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x180: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x188: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x190: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x198: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1a0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1a8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1b0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1b8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1c0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1c8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1d0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1d8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1e0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1e8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1f0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x1f8: */  0x00, 0x00, 0x00, 0x1c, 0x00, 0x3c, 0x3f, 0x3f,
/* 0x200: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x208: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x210: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x218: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x220: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x228: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x230: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x238: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x240: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x248: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x250: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x258: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x260: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x268: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x270: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x278: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x280: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x288: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x290: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x298: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2a0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2a8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2b0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2b8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2c0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2c8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2d0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2d8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2e0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2e8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2f0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x2f8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x5e, 0x5f,
/* 0x300: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x308: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x310: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x318: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x320: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x328: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x330: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x338: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x340: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x348: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x350: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x358: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x360: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x368: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x370: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
/* 0x378: */  0x00, 0x00, 0x00, 0x40, 0x40, 0x60, 0x60, 0x6f,
/* 0x380: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x388: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x390: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x398: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
/* 0x3a0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x3a8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40,
/* 0x3b0: */  0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x60,
/* 0x3b8: */  0x40, 0x40, 0x60, 0x60, 0x60, 0x60, 0x70, 0x77,
/* 0x3c0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40,
/* 0x3c8: */  0x40, 0x40, 0x40, 0x40, 0x40, 0x60, 0x60, 0x60,
/* 0x3d0: */  0x40, 0x40, 0x40, 0x60, 0x60, 0x60, 0x60, 0x70,
/* 0x3d8: */  0x60, 0x60, 0x60, 0x70, 0x70, 0x70, 0x78, 0x7b,
/* 0x3e0: */  0x60, 0x60, 0x60, 0x70, 0x60, 0x70, 0x70, 0x70,
/* 0x3e8: */  0x70, 0x70, 0x70, 0x78, 0x78, 0x78, 0x78, 0x7c,
/* 0x3f0: */  0x78, 0x78, 0x78, 0x7c, 0x78, 0x7c, 0x7c, 0x7e,
/* 0x3f8: */  0x7c, 0x7e, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
/* 0x400: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x408: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x410: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x418: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x420: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x428: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x430: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x438: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x440: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x448: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x450: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x458: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x460: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x468: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x470: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x478: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
/* 0x480: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x488: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x490: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x498: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x4a0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x4a8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x4b0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x4b8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
/* 0x4c0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x4c8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
/* 0x4d0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
/* 0x4d8: */  0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x4e0: */  0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x4e8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x4f0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x4f8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x8e, 0x9f,
/* 0x500: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x508: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x510: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x518: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
/* 0x520: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0x528: */  0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x80, 0x80,
/* 0x530: */  0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x538: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x540: */  0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x80, 0x80,
/* 0x548: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x550: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x558: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x560: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x568: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x570: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x578: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xaf,
/* 0x580: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x588: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x590: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x598: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x5a0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x5a8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x5b0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x5b8: */  0x80, 0x80, 0x80, 0xa0, 0xa0, 0xa0, 0xa0, 0xb7,
/* 0x5c0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x5c8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xa0,
/* 0x5d0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xa0, 0xa0,
/* 0x5d8: */  0xa0, 0xa0, 0xa0, 0xb0, 0xa0, 0xb0, 0xb0, 0xbb,
/* 0x5e0: */  0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xb0, 0xb0,
/* 0x5e8: */  0xa0, 0xb0, 0xb0, 0xb8, 0xb0, 0xb8, 0xb8, 0xbc,
/* 0x5f0: */  0xb0, 0xb8, 0xb8, 0xb8, 0xb8, 0xbc, 0xbc, 0xbe,
/* 0x5f8: */  0xbc, 0xbc, 0xbe, 0xbf, 0xbe, 0xbf, 0xbf, 0xbf,
/* 0x600: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x608: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x610: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x618: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x620: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x628: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x630: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x638: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xc0,
/* 0x640: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x648: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x650: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0,
/* 0x658: */  0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x660: */  0x80, 0x80, 0x80, 0xc0, 0x80, 0xc0, 0xc0, 0xc0,
/* 0x668: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x670: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x678: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xcf,
/* 0x680: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xc0,
/* 0x688: */  0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x690: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x698: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x6a0: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x6a8: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x6b0: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x6b8: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xd7,
/* 0x6c0: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x6c8: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x6d0: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x6d8: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xd0, 0xd0, 0xd9,
/* 0x6e0: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xd0,
/* 0x6e8: */  0xc0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd8, 0xd8, 0xdc,
/* 0x6f0: */  0xd0, 0xd0, 0xd8, 0xd8, 0xd8, 0xdc, 0xdc, 0xde,
/* 0x6f8: */  0xdc, 0xdc, 0xde, 0xdf, 0xde, 0xdf, 0xdf, 0xdf,
/* 0x700: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x708: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x710: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x718: */  0xc0, 0xc0, 0xc0, 0xe0, 0xc0, 0xe0, 0xe0, 0xe0,
/* 0x720: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0,
/* 0x728: */  0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x730: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x738: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe7,
/* 0x740: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x748: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x750: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x758: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe8,
/* 0x760: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x768: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe8, 0xec,
/* 0x770: */  0xe0, 0xe0, 0xe0, 0xe8, 0xe8, 0xe8, 0xec, 0xee,
/* 0x778: */  0xec, 0xec, 0xec, 0xee, 0xee, 0xef, 0xef, 0xef,
/* 0x780: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x788: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0,
/* 0x790: */  0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x798: */  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x7a0: */  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x7a8: */  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf4,
/* 0x7b0: */  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf4,
/* 0x7b8: */  0xf0, 0xf4, 0xf4, 0xf6, 0xf6, 0xf7, 0xf7, 0xf7,
/* 0x7c0: */  0xf0, 0xf0, 0xf0, 0xf8, 0xf0, 0xf8, 0xf8, 0xf8,
/* 0x7c8: */  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
/* 0x7d0: */  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
/* 0x7d8: */  0xf8, 0xf8, 0xf8, 0xfa, 0xfa, 0xfb, 0xfb, 0xfb,
/* 0x7e0: */  0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
/* 0x7e8: */  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfd, 0xfd, 0xfd,
/* 0x7f0: */  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
/* 0x7f8: */  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
/* 0x800: */  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
/* 0x808: */  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc,
/* 0x810: */  0xfd, 0xfd, 0xfd, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
/* 0x818: */  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8,
/* 0x820: */  0xfb, 0xfb, 0xfb, 0xfa, 0xfa, 0xf8, 0xf8, 0xf8,
/* 0x828: */  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
/* 0x830: */  0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
/* 0x838: */  0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x840: */  0xf7, 0xf7, 0xf7, 0xf6, 0xf6, 0xf4, 0xf4, 0xf0,
/* 0x848: */  0xf4, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x850: */  0xf4, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x858: */  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x860: */  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
/* 0x868: */  0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0,
/* 0x870: */  0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x878: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x880: */  0xef, 0xef, 0xef, 0xee, 0xee, 0xec, 0xec, 0xe8,
/* 0x888: */  0xee, 0xec, 0xe8, 0xe8, 0xe8, 0xe0, 0xe0, 0xe0,
/* 0x890: */  0xec, 0xe8, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x898: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x8a0: */  0xe8, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x8a8: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x8b0: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x8b8: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x8c0: */  0xe7, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x8c8: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
/* 0x8d0: */  0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0,
/* 0x8d8: */  0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x8e0: */  0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x8e8: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x8f0: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x8f8: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x900: */  0xdf, 0xdf, 0xdf, 0xde, 0xdf, 0xde, 0xdc, 0xdc,
/* 0x908: */  0xde, 0xdc, 0xdc, 0xd8, 0xd8, 0xd8, 0xd0, 0xd0,
/* 0x910: */  0xdc, 0xd8, 0xd8, 0xd0, 0xd0, 0xd0, 0xd0, 0xc0,
/* 0x918: */  0xd0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x920: */  0xd9, 0xd0, 0xd0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x928: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x930: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x938: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x940: */  0xd7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x948: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x950: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x958: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x960: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x968: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x970: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80,
/* 0x978: */  0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x980: */  0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x988: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x990: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
/* 0x998: */  0xc0, 0xc0, 0xc0, 0x80, 0xc0, 0x80, 0x80, 0x80,
/* 0x9a0: */  0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80,
/* 0x9a8: */  0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9b0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9b8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9c0: */  0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9c8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9d0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9d8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9e0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9e8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9f0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0x9f8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa00: */  0xbf, 0xbf, 0xbf, 0xbe, 0xbf, 0xbe, 0xbc, 0xbc,
/* 0xa08: */  0xbe, 0xbc, 0xbc, 0xb8, 0xb8, 0xb8, 0xb8, 0xb0,
/* 0xa10: */  0xbc, 0xb8, 0xb8, 0xb0, 0xb8, 0xb0, 0xb0, 0xb0,
/* 0xa18: */  0xb0, 0xb0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0,
/* 0xa20: */  0xbb, 0xb0, 0xb0, 0xa0, 0xb0, 0xa0, 0xa0, 0xa0,
/* 0xa28: */  0xa0, 0xa0, 0xa0, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa30: */  0xa0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa38: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa40: */  0xb7, 0xb0, 0xa0, 0xa0, 0xa0, 0x80, 0x80, 0x80,
/* 0xa48: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa50: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa58: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa60: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa68: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa70: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa78: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa80: */  0xaf, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa88: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa90: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xa98: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xaa0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xaa8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xab0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xab8: */  0x80, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00,
/* 0xac0: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xac8: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
/* 0xad0: */  0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
/* 0xad8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xae0: */  0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xae8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xaf0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xaf8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb00: */  0x9f, 0x9e, 0x88, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xb08: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xb10: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
/* 0xb18: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
/* 0xb20: */  0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
/* 0xb28: */  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb30: */  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb38: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb40: */  0x80, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00,
/* 0xb48: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb50: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb58: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb60: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb68: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb70: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb78: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb80: */  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb88: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb90: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xb98: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xba0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xba8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbb0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbb8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbc0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbc8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbd0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbd8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbe0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbe8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbf0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xbf8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc00: */  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e, 0x7c,
/* 0xc08: */  0x7e, 0x7c, 0x7c, 0x78, 0x7c, 0x78, 0x78, 0x78,
/* 0xc10: */  0x7c, 0x78, 0x78, 0x78, 0x78, 0x70, 0x70, 0x70,
/* 0xc18: */  0x78, 0x70, 0x70, 0x60, 0x70, 0x60, 0x60, 0x60,
/* 0xc20: */  0x7b, 0x78, 0x70, 0x70, 0x70, 0x60, 0x60, 0x60,
/* 0xc28: */  0x70, 0x60, 0x60, 0x60, 0x60, 0x40, 0x40, 0x40,
/* 0xc30: */  0x60, 0x60, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40,
/* 0xc38: */  0x40, 0x40, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00,
/* 0xc40: */  0x77, 0x70, 0x60, 0x60, 0x60, 0x60, 0x40, 0x40,
/* 0xc48: */  0x60, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00,
/* 0xc50: */  0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc58: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc60: */  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc68: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc70: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc78: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc80: */  0x6f, 0x64, 0x60, 0x40, 0x40, 0x00, 0x00, 0x00,
/* 0xc88: */  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc90: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xc98: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xca0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xca8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcb0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcb8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcc0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcc8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcd0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcd8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xce0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xce8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcf0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xcf8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd00: */  0x5f, 0x5e, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd08: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd10: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd18: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd20: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd28: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd30: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd38: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd40: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd48: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd50: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd58: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd60: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd68: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd70: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd78: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd80: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd88: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd90: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xd98: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xda0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xda8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdb0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdb8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdc0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdc8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdd0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdd8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xde0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xde8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdf0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xdf8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe00: */  0x3f, 0x3f, 0x3e, 0x00, 0x1c, 0x00, 0x00, 0x00,
/* 0xe08: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe10: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe18: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe20: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe28: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe30: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe38: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe40: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe48: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe50: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe58: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe60: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe68: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe70: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe78: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe80: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe88: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe90: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xe98: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xea0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xea8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xeb0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xeb8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xec0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xec8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xed0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xed8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xee0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xee8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xef0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xef8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf00: */  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf08: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf10: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf18: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf20: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf28: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf30: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf38: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf40: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf48: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf50: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf58: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf60: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf68: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf70: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf78: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf80: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf88: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf90: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xf98: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfa0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfa8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfb0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfb8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfc0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfc8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfd0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfd8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfe0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xfe8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xff0: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 0xff8: */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
