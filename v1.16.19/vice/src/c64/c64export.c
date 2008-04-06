/*
 * c64export.c - Expansion port handling for the C64.
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

#include "vice.h"

#include <stdio.h>
#include <string.h>

#include "c64export.h"
#ifdef HAS_TRANSLATION
#include "translate.h"
#endif
#include "ui.h"
#include "sid-resources.h"


static const char *usage_io1, *usage_io2, *usage_roml, *usage_romh;


int c64export_query(const c64export_resource_t *export_res)
{
    if (export_res->use_io1 > 0) {
        if (usage_io1 != NULL && strcmp(usage_io1, export_res->name)!=0) {
#ifdef HAS_TRANSLATION
            ui_error(translate_text(IDGS_RESOURCE_S_BLOCKED_BY_S),"IO1", usage_io1);
#else
            ui_error(_("Resource %s blocked by %s."),"IO1", usage_io1);
#endif
            return -1;
        }
        if (sid_stereo && sid_stereo_address_start >= 0xde00 && sid_stereo_address_start <=0xdeff && checking_sid_stereo==0) {
#ifdef HAS_TRANSLATION
            ui_error(translate_text(IDGS_RESOURCE_S_BLOCKED_BY_S),"IO1","STEREO_SID");
#else
            ui_error(_("Resource %s blocked by %s."),"IO1","STEREO_SID");
#endif
            return -1;
        }
    }
    if (export_res->use_io2 > 0) {
        if (usage_io2 != NULL && strcmp(usage_io2, export_res->name)!=0) {
#ifdef HAS_TRANSLATION
            ui_error(translate_text(IDGS_RESOURCE_S_BLOCKED_BY_S),"IO2", usage_io2);
#else
            ui_error(_("Resource %s blocked by %s."),"IO2", usage_io2);
#endif
            return -1;
        }
        if (sid_stereo && sid_stereo_address_start >= 0xdf00 && sid_stereo_address_start <=0xdfff&& checking_sid_stereo==0) {
#ifdef HAS_TRANSLATION
            ui_error(translate_text(IDGS_RESOURCE_S_BLOCKED_BY_S),"IO2","STEREO_SID.");
#else
            ui_error(_("Resource %s blocked by %s."),"IO2","STEREO_SID.");
#endif
            return -1;
        }
    }
    if (export_res->use_roml > 0) {
        if (usage_roml != NULL && strcmp(usage_roml, export_res->name)!=0) {
#ifdef HAS_TRANSLATION
            ui_error(translate_text(IDGS_RESOURCE_S_BLOCKED_BY_S),"ROML", usage_roml);
#else
            ui_error(_("Resource %s blocked by %s."),"ROML", usage_roml);
#endif
           return -1;
        }
    }
    if (export_res->use_romh > 0) {
        if (usage_romh != NULL && strcmp(usage_romh, export_res->name)!=0) {
#ifdef HAS_TRANSLATION
            ui_error(translate_text(IDGS_RESOURCE_S_BLOCKED_BY_S),"ROMH", usage_romh);
#else
            ui_error(_("Resource %s blocked by %s."),"ROMH", usage_romh);
#endif
            return -1;
        }
    }

    return 0;
}

int c64export_add(const c64export_resource_t *export_res)
{
    if (c64export_query(export_res) < 0)
        return -1;

    if (export_res->use_io1 > 0)
        usage_io1 = export_res->name;
    if (export_res->use_io2 > 0)
        usage_io2 = export_res->name;
    if (export_res->use_roml > 0)
        usage_roml = export_res->name;
    if (export_res->use_romh > 0)
        usage_romh = export_res->name;

    return 0;
}

int c64export_remove(const c64export_resource_t *export_res)
{
    if (export_res->use_io1 > 0) {
        if (usage_io1 == NULL)
            return -1;
    }
    if (export_res->use_io2 > 0) {
        if (usage_io2 == NULL)
            return -1;
    }
    if (export_res->use_roml > 0) {
        if (usage_roml == NULL)
            return -1;
    }
    if (export_res->use_romh > 0) {
        if (usage_romh == NULL)
            return -1;
    }

    if (export_res->use_io1 > 0)
        usage_io1 = NULL;
    if (export_res->use_io2 > 0)
        usage_io2 = NULL;
    if (export_res->use_roml > 0)
        usage_roml = NULL;
    if (export_res->use_romh > 0)
        usage_romh = NULL;

    return 0;
}

int c64export_resources_init(void)
{
    usage_io1 = NULL;
    usage_io2 = NULL;
    usage_roml = NULL;
    usage_romh = NULL;

    return 0;
}

