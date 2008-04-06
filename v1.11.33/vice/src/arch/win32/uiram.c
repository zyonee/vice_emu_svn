/*
 * uiram.c - Implementation of the RAM settings dialog box.
 *
 * Written by
 *  Andreas Matthies <andreas.matthies@gmx.net>
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

#include <string.h>
#include <windows.h>

#include "lib.h"
#include "ram.h"
#include "res.h"
#include "resources.h"
#include "ui.h"
#include "uiram.h"
#include "winmain.h"


static int ui_ram_startvalue[]={
    0, 255, -1
};

static int ui_ram_invertvalue[]={
    0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, -1
};

static int orig_startvalue;
static int orig_valueinvert;
static int orig_patterninvert;


static void update_preview(HWND hwnd)
{
    const char *s;
    char *s_win;
    int i, j;

    s = ram_init_print_pattern();

    s_win = lib_malloc(2 * strlen(s) + 1);
    i = j =0;
    while(s[i] != '\0') {
        if(s[i] == '\n')
            s_win[j++] = '\r';
        s_win[j++] = s[i++];
    }
    s_win[j] = '\0';

    SetDlgItemText(hwnd, IDC_RAMINIT_PREVIEW, s_win);
    lib_free(s_win);
}


static void init_ram_dialog(HWND hwnd)
{
HWND    temp_hwnd, temp_hwnd2;
int     i;
HFONT hfont;

    hfont = CreateFont(-12,-7,0,0,400,0,0,0,0,0,0,
                    DRAFT_QUALITY,FIXED_PITCH|FF_MODERN,NULL);

    if (hfont)
        SendDlgItemMessage(hwnd,IDC_RAMINIT_PREVIEW,WM_SETFONT,
            (WPARAM)hfont,MAKELPARAM(TRUE,0));

    resources_get_value("RAMInitStartValue", (resource_value_t *)&orig_startvalue);
    temp_hwnd=GetDlgItem(hwnd,IDC_RAMINIT_STARTVALUE);

    for (i = 0; ui_ram_startvalue[i] >= 0; i++)
    {
        char s[16];

        itoa(ui_ram_startvalue[i], s, 10);
        SendMessage(temp_hwnd,CB_ADDSTRING,0,(LPARAM)s);
        if (orig_startvalue == ui_ram_startvalue[i])
            SendMessage(temp_hwnd,CB_SETCURSEL,(WPARAM)i,0);
    }

    resources_get_value("RAMInitValueInvert", (resource_value_t *)&orig_valueinvert);
    resources_get_value("RAMInitPatternInvert", (resource_value_t *)&orig_patterninvert);
    temp_hwnd=GetDlgItem(hwnd,IDC_RAMINIT_VALUEINVERT);
    temp_hwnd2=GetDlgItem(hwnd,IDC_RAMINIT_PATTERNINVERT);
    
    for (i = 0; ui_ram_invertvalue[i] >= 0; i++)
    {
        char s[16];

        itoa(ui_ram_invertvalue[i],s,10);
        SendMessage(temp_hwnd,CB_ADDSTRING,0,(LPARAM)s);
        SendMessage(temp_hwnd2,CB_ADDSTRING,0,(LPARAM)s);
        if (ui_ram_invertvalue[i] == orig_valueinvert)
            SendMessage(temp_hwnd,CB_SETCURSEL,(WPARAM)i,0);
        if (ui_ram_invertvalue[i] == orig_patterninvert)
            SendMessage(temp_hwnd2,CB_SETCURSEL,(WPARAM)i,0);
    }

    update_preview(hwnd);
}


static BOOL CALLBACK dialog_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    int command;
    int rv;

    switch (msg) {
        case WM_COMMAND:
            command=LOWORD(wparam);
            switch (command) {
                case IDC_RAMINIT_STARTVALUE:
                    rv = SendMessage(GetDlgItem(
                            hwnd,IDC_RAMINIT_STARTVALUE),CB_GETCURSEL,0,0);
                    resources_set_value("RAMInitStartValue", 
                        (resource_value_t) ui_ram_startvalue[rv]);
                    update_preview(hwnd);
                    break;
                case IDC_RAMINIT_VALUEINVERT:
                    rv = SendMessage(GetDlgItem(
                            hwnd,IDC_RAMINIT_VALUEINVERT),CB_GETCURSEL,0,0);
                    resources_set_value("RAMInitValueInvert", 
                        (resource_value_t) ui_ram_invertvalue[rv]);
                    update_preview(hwnd);
                    break;
                case IDC_RAMINIT_PATTERNINVERT:
                    rv = SendMessage(GetDlgItem(
                            hwnd,IDC_RAMINIT_PATTERNINVERT),CB_GETCURSEL,0,0);
                    resources_set_value("RAMInitPatternInvert", 
                        (resource_value_t) ui_ram_invertvalue[rv]);
                    update_preview(hwnd);
                    break;

                case IDOK:
                    EndDialog(hwnd,0);
                    return TRUE;
                case IDCANCEL:
                    resources_set_value("RAMInitStartValue", 
                        (resource_value_t) orig_startvalue);
                    resources_set_value("RAMInitValueInvert", 
                        (resource_value_t) orig_valueinvert);
                    resources_set_value("RAMInitPatternInvert", 
                        (resource_value_t) orig_patterninvert);
                    EndDialog(hwnd,0);
                    return TRUE;
            }
            return FALSE;
        case WM_CLOSE:
            EndDialog(hwnd,0);
            return TRUE;
        case WM_INITDIALOG:
            init_ram_dialog(hwnd);
            return TRUE;
    }
    return FALSE;
}


void ui_ram_settings_dialog(HWND hwnd)
{
    DialogBox(winmain_instance,(LPCTSTR)IDD_RAM_SETTINGS_DIALOG,hwnd,dialog_proc);
}

