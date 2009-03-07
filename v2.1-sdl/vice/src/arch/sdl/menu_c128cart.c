/*
 * menu_c128cart.c - Implementation of the c128 cartridge settings menu for the SDL UI.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cartridge.h"
#include "menu_c128cart.h"
#include "menu_common.h"
#include "menu_c64cart_common.h"
#include "ui.h"
#include "uimenu.h"

UI_MENU_DEFINE_TOGGLE(CartridgeReset)

UI_MENU_DEFINE_TOGGLE(InternalFunctionROM)
UI_MENU_DEFINE_TOGGLE(ExternalFunctionROM)
UI_MENU_DEFINE_FILE_STRING(InternalFunctionName)
UI_MENU_DEFINE_FILE_STRING(ExternalFunctionName)

static const ui_menu_entry_t function_rom_menu[] = {
    SDL_MENU_ITEM_TITLE("Internal function ROM"),
    { "Enable",
      MENU_ENTRY_RESOURCE_TOGGLE,
      toggle_InternalFunctionROM_callback,
      NULL },
    { "ROM file",
      MENU_ENTRY_DIALOG,
      file_string_InternalFunctionName_callback,
      (ui_callback_data_t)"Select internal function ROM image" },
    SDL_MENU_ITEM_SEPARATOR,
    SDL_MENU_ITEM_TITLE("External function ROM"),
    { "Enable",
      MENU_ENTRY_RESOURCE_TOGGLE,
      toggle_ExternalFunctionROM_callback,
      NULL },
    { "ROM file",
      MENU_ENTRY_DIALOG,
      file_string_ExternalFunctionName_callback,
      (ui_callback_data_t)"Select external function ROM image" },
    { NULL }
};

const ui_menu_entry_t c128cart_menu[] = {
    { "Attach CRT image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_CRT },
    { "Attach generic 8KB image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_GENERIC_8KB },
    { "Attach generic 16KB image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_GENERIC_16KB },
    { "Attach action replay image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_ACTION_REPLAY },
    { "Attach action replay 3 image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_ACTION_REPLAY3 },
    { "Attach action replay 4 image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_ACTION_REPLAY4 },
    { "Attach atomic power image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_ATOMIC_POWER },
    { "Attach epyx fastload image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_EPYX_FASTLOAD },
    { "Attach IDE64 interface image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_IDE64 },
    { "Attach IEEE488 interface image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_IEEE488 },
    { "Attach retro replay image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_RETRO_REPLAY },
    { "Attach stardos image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_STARDOS },
    { "Attach structured basic image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_STRUCTURED_BASIC },
    { "Attach super snapshot 4 image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_SUPER_SNAPSHOT },
    { "Attach super snapshot 5 image",
      MENU_ENTRY_DIALOG,
      attach_c64_cart_callback,
      (ui_callback_data_t)CARTRIDGE_SUPER_SNAPSHOT_V5 },
    SDL_MENU_ITEM_SEPARATOR,
    { "Detach cartridge image",
      MENU_ENTRY_OTHER,
      detach_c64_cart_callback,
      NULL },
    { "Cartridge freeze",
      MENU_ENTRY_OTHER,
      c64_cart_freeze_callback,
      NULL },
    { "Set current cartridge as default",
      MENU_ENTRY_OTHER,
      set_c64_cart_default_callback,
      NULL },
    { "Reset on cartridge change",
      MENU_ENTRY_RESOURCE_TOGGLE,
      toggle_CartridgeReset_callback,
      NULL },
    SDL_MENU_ITEM_SEPARATOR,
    { "Expert cartridge settings",
      MENU_ENTRY_SUBMENU,
      submenu_callback,
      (ui_callback_data_t)expert_cart_menu },
    { "Function ROM settings",
      MENU_ENTRY_SUBMENU,
      submenu_callback,
      (ui_callback_data_t)function_rom_menu },
    { NULL }
};
