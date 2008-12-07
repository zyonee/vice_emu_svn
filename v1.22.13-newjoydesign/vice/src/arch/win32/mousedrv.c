/*
 * mousedrv.c - Mouse handling for Win32
 *
 * Written by
 *  Tibor Biczo <crown@mail.matav.hu>
 *  Ettore Perazzoli <ettore@comm2000.it>
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
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "vice.h"

#include <windows.h>
#include <stdio.h>

#include "log.h"
#include "mouse.h"
#include "mousedrv.h"
#include "types.h"
#include "ui.h"


int _mouse_x, _mouse_y;
#ifdef HAVE_DINPUT
#include "dinput_handle.h"
static int mouse_acquired = 0;
static LPDIRECTINPUTDEVICE di_mouse = NULL;


#endif

/* ------------------------------------------------------------------------- */

void mousedrv_mouse_changed(void)
{
    mouse_update_mouse_acquire();
}

int mousedrv_resources_init(void)
{
    return 0;
}

int mousedrv_cmdline_options_init(void)
{
    return 0;
}

/* ------------------------------------------------------------------------- */

void mousedrv_init(void)
{
#ifdef HAVE_DINPUT
    IDirectInput_CreateDevice(get_directinput_handle(), (GUID *)&GUID_SysMouse, &di_mouse,
                                            NULL);

#endif
}

void mouse_update_mouse_acquire(void)
{
#ifdef HAVE_DINPUT
    HRESULT res;
    if (di_mouse == NULL)
        return;
    if (_mouse_enabled) {
        if (ui_active) {
            res = IDirectInputDevice_SetCooperativeLevel( 	 
	              di_mouse, ui_active_window, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
            res = IDirectInputDevice_Acquire(di_mouse);
            mouse_acquired = 1;
        } else {
            IDirectInputDevice_Unacquire(di_mouse);
            mouse_acquired = 0;
        }
    } else {
        if (mouse_acquired) {
            IDirectInputDevice_Unacquire(di_mouse);
            mouse_acquired = 0;
        }
    }
#endif
}

BYTE mousedrv_get_x(void)
{
    if (!_mouse_enabled)
        return 0xff;
    return (BYTE)(_mouse_x >> 1) & 0x7e;
}

BYTE mousedrv_get_y(void)
{
    if (!_mouse_enabled)
        return 0xff;
    return (BYTE)(~_mouse_y >> 1) & 0x7e;
}

