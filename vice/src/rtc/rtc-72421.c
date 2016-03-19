/*
 * rtc-72421.c - RTC-72421 RTC emulation.
 *
 * Written by
 *  Marco van den Heuvel <blackystardust68@yahoo.com>
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

#include "rtc-72421.h"
#include "lib.h"
#include "rtc.h"

#include <string.h>

/* The RTC-72421 is a 4bit address/data line RTC module,
 * The RTC has the following features:
 * - Real-Time Clock Counts seconds, minutes, hours, date of the month,
 *   months, and years
 * - All registers are decimal
 */

/* The RTC-72421 has the following clock registers:
 *
 * register 0 : bits 3-0 seconds
 *
 * register 1 : bit  3   0
 *              bits 2-0 10 seconds
 *
 * register 2 : bits 3-0 minutes
 *
 * register 3 : bit  3   0
 *              bits 2-0 10 minutes
 *
 * register 4 : bits 3-0 hours
 *
 * register 5 : bit  3   24/12 hour selection (0 = 12 hour, 1 = 24 hour)
 *              bit  2   AM/PM indication bit (1 when in 12 hour mode, otherwise 0)
 *              bits 1-0 10 hours
 *
 * register 6 : bits 3-0 day of the month
 *
 * register 7 : bits 3-2 leapyear indicator
 *              bits 1-0 10 day of the month
 *
 * register 8 : bits 3-0 months
 *
 * register 9 : bits 3-1 0
 *              bit  0   10 months
 *
 * register A : bits 3-0 years
 *
 * register B : bits 3-0 10 years
 *
 * register C : bit  3   0
 *              bits 2-0 weekdays
 *
 * register D : bits 3-0 0
 *
 * register E : bits 3-0 0
 *
 * register F : bit  3   0
 *              bit  2   AM/PM selector
 *              bit  1   Clock Halt
 *              bit  0   0
 */

/* This module is currently used in the following emulated hardware:
 */

/* ---------------------------------------------------------------------------------------------------- */

rtc_72421_t *rtc72421_init(char *device)
{
    rtc_72421_t *retval = lib_calloc(1, sizeof(rtc_72421_t));
    int loaded = rtc_load_context(device, 0, 0);

    if (loaded) {
        retval->offset = rtc_get_loaded_offset();
    } else {
        retval->offset = 0;
    }
    retval->old_offset = retval->offset;

    retval->hour24 = 0;
    retval->device = lib_stralloc(device);

    return retval;
}

void rtc72421_destroy(rtc_72421_t *context, int save)
{
    if (save) {
        if (context->old_offset != context->offset) {
            rtc_save_context(NULL, 0, NULL, 0, context->device, context->offset);
        }
    }
    lib_free(context->device);
    lib_free(context);
}

/* ---------------------------------------------------------------------------------------------------- */

BYTE rtc72421_read(rtc_72421_t *context, BYTE address)
{
    BYTE retval = 0;
    time_t latch = (context->stop) ? context->latch : rtc_get_latch(context->offset);

    switch (address & 0xf) {
        case RTC72421_REGISTER_SECONDS:
            retval = rtc_get_second(latch, 0);
            retval %= 10;
            break;
        case RTC72421_REGISTER_10SECONDS:
            retval = rtc_get_second(latch, 0);
            retval /= 10;
            break;
        case RTC72421_REGISTER_MINUTES:
            retval = rtc_get_minute(latch, 0);
            retval %= 10;
            break;
        case RTC72421_REGISTER_10MINUTES:
            retval = rtc_get_minute(latch, 0);
            retval /= 10;
            break;
        case RTC72421_REGISTER_HOURS:
            if (context->hour24) {
                retval = rtc_get_hour(latch, 0);
            } else {
                retval = rtc_get_hour_am_pm(latch, 0);
                retval &= 0x1f;
            }
            retval %= 10;
            break;
        case RTC72421_REGISTER_10HOURS:
            if (context->hour24) {
                retval = rtc_get_hour(latch, 0);
                retval /= 10;
                retval |= 8;
            } else {
                retval = rtc_get_hour_am_pm(latch, 0);
                if (retval > 23) {
                    retval = (retval - 32) / 10;
                    retval |= 4;
                } else {
                    retval /= 10;
                }
            }
            break;
        case RTC72421_REGISTER_WEEKDAYS:
            retval = rtc_get_weekday(latch) - 1;
            if (retval > 6) {
                retval = 6;
            }
            break;
        case RTC72421_REGISTER_MONTHDAYS:
            retval = rtc_get_day_of_month(latch, 0);
            retval %= 10;
            break;
        case RTC72421_REGISTER_10MONTHDAYS:
            retval = rtc_get_day_of_month(latch, 0);
            retval /= 10;
            break;
        case RTC72421_REGISTER_MONTHS:
            retval = rtc_get_month(latch, 0);
            retval %= 10;
            break;
        case RTC72421_REGISTER_10MONTHS:
            retval = rtc_get_month(latch, 0);
            retval /= 10;
            break;
        case RTC72421_REGISTER_YEARS:
            retval = rtc_get_year(latch, 0);
            retval %= 10;
            break;
        case RTC72421_REGISTER_10YEARS:
            retval = rtc_get_year(latch, 0);
            retval /= 10;
            break;
        case RTC72421_REGISTER_CTRL2:
            retval = context->hour24 ? 2 : 0;
            retval |= context->stop ? 1 : 0;
            break;
    }
    return retval;
}


#define LIMIT_9(x) (x > 9) ? 9 : x

void rtc72421_write(rtc_72421_t *context, BYTE address, BYTE data)
{
    time_t latch = (context->stop) ? context->latch : rtc_get_latch(context->offset);
    BYTE real_data = data & 0xf;
    BYTE new_data;

    switch (address & 0xf) {
        case RTC72421_REGISTER_SECONDS:
            new_data = rtc_get_second(latch, 0);
            new_data /= 10;
            new_data *= 10;
            new_data += LIMIT_9(real_data);
            if (context->stop) {
                context->latch = rtc_set_latched_second(new_data, latch, 0);
            } else {
                context->offset = rtc_set_second(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_10SECONDS:
            new_data = rtc_get_second(latch, 0);
            new_data %= 10;
            new_data += ((real_data & 7) * 10);
            if (context->stop) {
                context->latch = rtc_set_latched_second(new_data, latch, 0);
            } else {
                context->offset = rtc_set_second(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_MINUTES:
            new_data = rtc_get_minute(latch, 0);
            new_data /= 10;
            new_data *= 10;
            new_data += LIMIT_9(real_data);
            if (context->stop) {
                context->latch = rtc_set_latched_minute(new_data, latch, 0);
            } else {
                context->offset = rtc_set_minute(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_10MINUTES:
            new_data = rtc_get_minute(latch, 0);
            new_data %= 10;
            new_data += ((real_data & 7) * 10);
            if (context->stop) {
                context->latch = rtc_set_latched_minute(new_data, latch, 0);
            } else {
                context->offset = rtc_set_minute(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_HOURS:
            if (context->hour24) {
                new_data = rtc_get_hour(latch, 0);
                new_data /= 10;
                new_data *= 10;
                new_data += LIMIT_9(real_data);
                if (context->stop) {
                    context->latch = rtc_set_latched_hour(new_data, latch, 0);
                } else {
                    context->offset = rtc_set_hour(new_data, context->offset, 0);
                }
            } else {
                new_data = rtc_get_hour_am_pm(latch, 0);
                if (new_data >= 32) {
                    new_data -= 32;
                    new_data /= 10;
                    new_data *= 10;
                    new_data += (LIMIT_9(real_data) + 32);
                } else {
                    new_data /= 10;
                    new_data *= 10;
                    new_data += LIMIT_9(real_data);
                }
                if (context->stop) {
                    context->latch = rtc_set_latched_hour_am_pm(new_data, latch, 0);
                } else {
                    context->offset = rtc_set_hour_am_pm(new_data, context->offset, 0);
                }
            }
            break;
        case RTC72421_REGISTER_10HOURS:
            if (real_data & 8) {
                new_data = rtc_get_hour(latch, 0);
                new_data %= 10;
                new_data += ((real_data & 3) * 10);
                context->hour24 = 1;
                if (context->stop) {
                    context->latch = rtc_set_latched_hour(new_data, latch, 0);
                } else {
                    context->offset = rtc_set_hour(new_data, context->offset, 0);
                }
            } else {
                real_data &= 7;
                new_data = rtc_get_hour_am_pm(latch, 0);
                if (new_data >= 32) {
                    new_data -= 32;
                }
                new_data %= 10;
                new_data += ((real_data & 3) * 10);
                if (real_data & 4) {
                    new_data += 32;
                }
                context->hour24 = 0;
                if (context->stop) {
                    context->latch = rtc_set_latched_hour_am_pm(new_data, latch, 0);
                } else {
                    context->offset = rtc_set_hour_am_pm(new_data, context->offset, 0);
                }
            }
            break;
        case RTC72421_REGISTER_WEEKDAYS:
            if (context->stop) {
                context->latch = rtc_set_latched_weekday(((real_data + 1) & 7), latch);
            } else {
                context->offset = rtc_set_weekday(((real_data + 1) & 7), context->offset);
            }
            break;
        case RTC72421_REGISTER_MONTHDAYS:
            new_data = rtc_get_day_of_month(latch, 0);
            new_data /= 10;
            new_data *= 10;
            new_data += LIMIT_9(real_data);
            if (context->stop) {
                context->latch = rtc_set_latched_day_of_month(new_data, latch, 0);
            } else {
                context->offset = rtc_set_day_of_month(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_10MONTHDAYS:
            new_data = rtc_get_day_of_month(latch, 0);
            new_data %= 10;
            new_data += ((real_data & 3) * 10);
            if (context->stop) {
                context->latch = rtc_set_latched_day_of_month(new_data, latch, 0);
            } else {
                context->offset = rtc_set_day_of_month(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_MONTHS:
            new_data = rtc_get_month(latch, 0);
            new_data /= 10;
            new_data *= 10;
            new_data += LIMIT_9(real_data);
            if (context->stop) {
                context->latch = rtc_set_latched_month(new_data, latch, 0);
            } else {
                context->offset = rtc_set_month(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_10MONTHS:
            new_data = rtc_get_month(latch, 0);
            new_data %= 10;
            new_data += ((real_data & 1) * 10);
            if (context->stop) {
                context->latch = rtc_set_latched_month(new_data, latch, 0);
            } else {
                context->offset = rtc_set_month(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_YEARS:
            new_data = rtc_get_year(latch, 0);
            new_data /= 10;
            new_data *= 10;
            new_data += LIMIT_9(real_data);
            if (context->stop) {
                context->latch = rtc_set_latched_year(new_data, latch, 0);
            } else {
                context->offset = rtc_set_year(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_10YEARS:
            new_data = rtc_get_year(latch, 0);
            new_data %= 10;
            new_data += (LIMIT_9(real_data) * 10);
            if (context->stop) {
                context->latch = rtc_set_latched_year(new_data, latch, 0);
            } else {
                context->offset = rtc_set_year(new_data, context->offset, 0);
            }
            break;
        case RTC72421_REGISTER_CTRL2:
            context->hour24 = (real_data & 4) ? 1: 0;
            if (real_data & 2) {
                context->stop = 1;
                context->latch = rtc_get_latch(context->offset);
            } else {
                context->stop = 0;
                context->offset = context->offset - (rtc_get_latch(0) - (context->latch - context->offset));
            }
            break;
    }
}
