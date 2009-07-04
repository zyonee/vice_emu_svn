/*
 * lightpendrv.c - Lightpen driver for SDL UI.
 *
 * Written by
 *  Hannu Nuotio <hannu.nuotio@tut.fi>
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
#include "types.h"

#include <SDL/SDL.h>

#include "lightpen.h"
#include "lightpendrv.h"
#include "videoarch.h"

/* ------------------------------------------------------------------ */
/* External interface */

sdl_lightpen_adjust_t sdl_lightpen_adjust;

void sdl_lightpen_update(void)
{
    int x, y, on_screen;
    Uint8 buttons;

    if (!lightpen_enabled) {
        return;
    }

    on_screen = SDL_GetAppState() & SDL_APPMOUSEFOCUS;

    if (on_screen) {
        buttons = SDL_GetMouseState(&x, &y);
    } else {
        x = y = -1;
        buttons = 0;
    }

#ifdef SDL_DEBUG
fprintf(stderr,"%s pre : x = %i, y = %i, buttons = %02x, on_screen = %i\n",__func__, x, y, buttons, on_screen);
#endif

    if (on_screen) {
        x -= sdl_lightpen_adjust.offset_x;
        y -= sdl_lightpen_adjust.offset_y;

        if ((x < 0) || (y < 0) || (x >= sdl_lightpen_adjust.max_x) || (y >= sdl_lightpen_adjust.max_y)) {
            on_screen = 0;
        } else {
            x *= sdl_lightpen_adjust.scale_x;
            y *= sdl_lightpen_adjust.scale_y;
        }
    }

    if (!on_screen) {
        x = y = -1;
    }

#ifdef SDL_DEBUG
fprintf(stderr,"%s post: x = %i, y = %i\n",__func__, x, y);
#endif

    lightpen_update(sdl_active_canvas_num, x, y, (int)buttons);
}
