/*
 * uicolor.c - X11 color routines.
 *
 * Written by
 *  Andreas Boose <boose@linux.rz.fh-hannover.de>
 *  Ettore Perazzoli <ettore@comm2000.it>
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

#include "vice.h"

#include <stdlib.h>
#include <X11/Xlib.h>

#include "color.h"
#include "log.h"
#include "palette.h"
#include "types.h"
#include "uicolor.h"
#include "utils.h"
#include "video.h"

extern int screen;
extern Colormap colormap;
extern Pixel drive_led_on_red_pixel, drive_led_on_green_pixel;
extern Pixel drive_led_off_pixel;

#define NUM_ENTRIES 3

static int uicolor_alloc_system_colors(void)
{
    palette_t *p = (palette_t *)xmalloc(sizeof(palette_t));
    PIXEL pixel_return[NUM_ENTRIES];
    unsigned long color_return[NUM_ENTRIES];

    p->num_entries = NUM_ENTRIES;
    p->entries = xmalloc(sizeof(palette_entry_t) * NUM_ENTRIES);
    memset(p->entries, 0, sizeof(palette_entry_t) * NUM_ENTRIES);

    p->entries[0].red = 0;
    p->entries[0].green = 0;
    p->entries[0].blue = 0;

    p->entries[1].red = 0xff;
    p->entries[1].green = 0;
    p->entries[1].blue = 0;

    p->entries[2].red = 0;
    p->entries[2].green = 0xff;
    p->entries[2].blue = 0;

    color_alloc_colors((void *)-1, p, pixel_return, color_return);

    drive_led_off_pixel = (Pixel)color_return[0];
    drive_led_on_red_pixel = (Pixel)color_return[1];
    drive_led_on_green_pixel = (Pixel)color_return[2];

    free(p->entries);
    free(p);

    return 0;
}

/*-----------------------------------------------------------------------*/

int uicolor_alloc_colors(canvas_t *c, const palette_t *palette,
                         PIXEL pixel_return[])
{
    log_message(LOG_DEFAULT, _("Color request for canvas %p."), c);

    if (uicolor_alloc_system_colors() < 0
        || color_alloc_colors(c, palette, pixel_return, NULL) < 0) {
        Display *display = ui_get_display_ptr();
        if (colormap == DefaultColormap(display, screen)) {
            log_warning(LOG_DEFAULT,
                        _("Automatically using a private colormap."));
            colormap = XCreateColormap(display, RootWindow(display, screen),
                                       visual, AllocNone);
            XtVaSetValues(_ui_top_level, XtNcolormap, colormap, NULL);
            return color_alloc_colors(c, palette, pixel_return, NULL);
        }
    }
    return 0;
}

int ui_canvas_set_palette(canvas_t *c, ui_window_t w, const palette_t *palette,
                          PIXEL *pixel_return)
{
    log_message(LOG_DEFAULT, _("Change color request for canvas %p."), c);

    return color_alloc_colors(c, palette, pixel_return, NULL);
}

/*-----------------------------------------------------------------------*/

static unsigned int bits_per_pixel;

int uicolor_alloc_color(unsigned int red, unsigned int green,
                        unsigned int blue, unsigned long *color_pixel,
                        PIXEL *pixel_return)
{
    XColor color;
    XImage *im;
    PIXEL *data = (PIXEL *)xmalloc(4);
    Display *display = ui_get_display_ptr();

    /* This is a kludge to map pixels to zimage values. Is there a better
       way to do this? //tvr */
    im = XCreateImage(display, visual, ui_get_display_depth(),
                      ZPixmap, 0, (char *)data, 1, 1, 8, 1);
    if (!im) {
        log_error(LOG_DEFAULT, _("XCreateImage failed."));
        return -1;
    }

    color.flags = DoRed | DoGreen | DoBlue;
    color.red =  red << 8;
    color.green =  green << 8;
    color.blue = blue << 8;

    if (!XAllocColor(display, colormap, &color)) {
        log_error(LOG_DEFAULT, _("Cannot allocate color \"#%04X%04X%04X\"."),
                  color.red, color.green, color.blue);
        XDestroyImage(im);
        return -1;
    }
    XPutPixel(im, 0, 0, color.pixel);

    bits_per_pixel = im->bits_per_pixel;

    *pixel_return = *data;
    *color_pixel = color.pixel;

    XDestroyImage(im);

    return 0;
}

void uicolor_free_color(unsigned int red, unsigned int green,
                        unsigned int blue, unsigned long color_pixel)
{
    if (!XFreeColors(ui_get_display_ptr(), colormap, &color_pixel, 1, 0))
        log_error(LOG_DEFAULT, _("XFreeColors failed."));
}

void uicolor_convert_color_table(unsigned int colnr, PIXEL *pixel_return,
                                 PIXEL *data, unsigned int dither,
                                 long color_pixel)
{
#if X_DISPLAY_DEPTH == 0
    video_convert_color_table(colnr, pixel_return, data, bits_per_pixel,
                              dither, color_pixel);
#endif
}

