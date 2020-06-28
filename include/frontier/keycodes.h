/*
 * Frontier - A toolkit for creating simple OS-independent user interfaces
 * Copyright (C) 2018, 2020 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Frontier.
 *
 * Frontier is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Frontier is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Frontier.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FRONTIER_SCANCODES_H_
#define __FRONTIER_SCANCODES_H_

namespace Frontier {
enum KeyCode
{
    KC_UNKNOWN                     = 0x0000,  /* Back space, back char */

    /*
     * TTY function keys, cleverly chosen to map to ASCII, for convenience of
     * programming, but could have been arbitrary (at the cost of lookup
     * tables in client code).
     */

    KC_BACKSPACE                     = 0x0008,  /* Back space, back char */
    KC_TAB                           = 0x0009,
    KC_LINEFEED                      = 0xff0a,  /* Linefeed, LF */
    KC_CLEAR                         = 0xff0b,
    KC_RETURN                        = 0x000d,  /* Return, enter */
    KC_PAUSE                         = 0xff13,  /* Pause, hold */
    KC_SCROLL_LOCK                   = 0xff14,
    KC_SYS_REQ                       = 0xff15,
    KC_ESCAPE                        = 0x001b,
    KC_DELETE                        = 0xffff,  /* Delete, rubout */

    /* Cursor control & motion */

    KC_HOME                          = 0xff50,
    KC_LEFT                          = 0xff51,  /* Move left, left arrow */
    KC_UP                            = 0xff52,  /* Move up, up arrow */
    KC_RIGHT                         = 0xff53,  /* Move right, right arrow */
    KC_DOWN                          = 0xff54,  /* Move down, down arrow */
    KC_PRIOR                         = 0xff55,  /* Prior, previous */
    KC_PAGE_UP                       = 0xff55,
    KC_NEXT                          = 0xff56,  /* Next */
    KC_PAGE_DOWN                     = 0xff56,
    KC_END                           = 0xff57,  /* EOL */
    KC_BEGIN                         = 0xff58,  /* BOL */


    /* Misc functions */

    KC_SELECT                        = 0xff60,  /* Select, mark */
    KC_PRINT_SCREEN                  = 0xff61,
    KC_EXECUTE                       = 0xff62,  /* Execute, run, do */
    KC_INSERT                        = 0xff63,  /* Insert, insert here */
    KC_UNDO                          = 0xff65,
    KC_REDO                          = 0xff66,  /* Redo, again */
    KC_MENU                          = 0xff67,
    KC_FIND                          = 0xff68,  /* Find, search */
    KC_CANCEL                        = 0xff69,  /* Cancel, stop, abort, exit */
    KC_HELP                          = 0xff6a,  /* Help */
    KC_BREAK                         = 0xff6b,
    KC_MODE_SWITCH                   = 0xff7e,  /* Character set switch */
    KC_SCRIPT_SWITCH                 = 0xff7e,  /* Alias for mode_switch */
    KC_NUM_LOCK                      = 0xff7f,

    /* Keypad functions, keypad numbers cleverly chosen to map to ASCII */

    KC_KP_SPACE                      = 0xff80,  /* Space */
    KC_KP_TAB                        = 0xff89,
    KC_KP_ENTER                      = 0xff8d,  /* Enter */
    KC_KP_F1                         = 0xff91,  /* PF1, KP_A, ... */
    KC_KP_F2                         = 0xff92,
    KC_KP_F3                         = 0xff93,
    KC_KP_F4                         = 0xff94,
    KC_KP_HOME                       = 0xff95,
    KC_KP_LEFT                       = 0xff96,
    KC_KP_UP                         = 0xff97,
    KC_KP_RIGHT                      = 0xff98,
    KC_KP_DOWN                       = 0xff99,
    KC_KP_PRIOR                      = 0xff9a,
    KC_KP_PAGE_UP                    = 0xff9a,
    KC_KP_NEXT                       = 0xff9b,
    KC_KP_PAGE_DOWN                  = 0xff9b,
    KC_KP_END                        = 0xff9c,
    KC_KP_BEGIN                      = 0xff9d,
    KC_KP_INSERT                     = 0xff9e,
    KC_KP_DELETE                     = 0xff9f,
    KC_KP_EQUAL                      = 0xffbd,  /* Equals */
    KC_KP_MULTIPLY                   = 0xffaa,
    KC_KP_ADD                        = 0xffab,
    KC_KP_COMMA                      = 0xffac,  /* Separator, often comma */
    KC_KP_SUBTRACT                   = 0xffad,
    KC_KP_DECIMAL                    = 0xffae,
    KC_KP_DIVIDE                     = 0xffaf,

    KC_KP_0                          = 0xffb0,
    KC_KP_1                          = 0xffb1,
    KC_KP_2                          = 0xffb2,
    KC_KP_3                          = 0xffb3,
    KC_KP_4                          = 0xffb4,
    KC_KP_5                          = 0xffb5,
    KC_KP_6                          = 0xffb6,
    KC_KP_7                          = 0xffb7,
    KC_KP_8                          = 0xffb8,
    KC_KP_9                          = 0xffb9,



    /*
     * Auxiliary functions; note the duplicate definitions for left and right
     * function keys;  Sun keyboards and a few other manufacturers have such
     * function key groups on the left and/or right sides of the keyboard.
     * We've not found a keyboard with more than 35 function keys total.
     */

    KC_F1                            = 0xffbe,
    KC_F2                            = 0xffbf,
    KC_F3                            = 0xffc0,
    KC_F4                            = 0xffc1,
    KC_F5                            = 0xffc2,
    KC_F6                            = 0xffc3,
    KC_F7                            = 0xffc4,
    KC_F8                            = 0xffc5,
    KC_F9                            = 0xffc6,
    KC_F10                           = 0xffc7,
    KC_F11                           = 0xffc8,
    KC_L1                            = 0xffc8,
    KC_F12                           = 0xffc9,
    KC_L2                            = 0xffc9,
    KC_F13                           = 0xffca,
    KC_L3                            = 0xffca,
    KC_F14                           = 0xffcb,
    KC_L4                            = 0xffcb,
    KC_F15                           = 0xffcc,
    KC_L5                            = 0xffcc,
    KC_F16                           = 0xffcd,
    KC_L6                            = 0xffcd,
    KC_F17                           = 0xffce,
    KC_L7                            = 0xffce,
    KC_F18                           = 0xffcf,
    KC_L8                            = 0xffcf,
    KC_F19                           = 0xffd0,
    KC_L9                            = 0xffd0,
    KC_F20                           = 0xffd1,
    KC_L10                           = 0xffd1,
    KC_F21                           = 0xffd2,
    KC_R1                            = 0xffd2,
    KC_F22                           = 0xffd3,
    KC_R2                            = 0xffd3,
    KC_F23                           = 0xffd4,
    KC_R3                            = 0xffd4,
    KC_F24                           = 0xffd5,
    KC_R4                            = 0xffd5,
    KC_F25                           = 0xffd6,
    KC_R5                            = 0xffd6,
    KC_F26                           = 0xffd7,
    KC_R6                            = 0xffd7,
    KC_F27                           = 0xffd8,
    KC_R7                            = 0xffd8,
    KC_F28                           = 0xffd9,
    KC_R8                            = 0xffd9,
    KC_F29                           = 0xffda,
    KC_R9                            = 0xffda,
    KC_F30                           = 0xffdb,
    KC_R10                           = 0xffdb,
    KC_F31                           = 0xffdc,
    KC_R11                           = 0xffdc,
    KC_F32                           = 0xffdd,
    KC_R12                           = 0xffdd,
    KC_F33                           = 0xffde,
    KC_R13                           = 0xffde,
    KC_F34                           = 0xffdf,
    KC_R14                           = 0xffdf,
    KC_F35                           = 0xffe0,
    KC_R15                           = 0xffe0,

    /* Modifiers */

    KC_SHIFT_L                       = 0xffe1,  /* Left shift */
    KC_SHIFT_R                       = 0xffe2,  /* Right shift */
    KC_CONTROL_L                     = 0xffe3,  /* Left control */
    KC_CONTROL_R                     = 0xffe4,  /* Right control */
    KC_CAPS_LOCK                     = 0xffe5,  /* Caps lock */
    KC_SHIFT_LOCK                    = 0xffe6,  /* Shift lock */

    KC_META_L                        = 0xffe7,  /* Left meta */
    KC_META_R                        = 0xffe8,  /* Right meta */
    KC_ALT_L                         = 0xffe9,  /* Left alt */
    KC_ALT_R                         = 0xffea,  /* Right alt */
    KC_SUPER_L                       = 0xffeb,  /* Left super */
    KC_SUPER_R                       = 0xffec,  /* Right super */
    KC_HYPER_L                       = 0xffed,  /* Left hyper */
    KC_HYPER_R                       = 0xffee,  /* Right hyper */

    KC_SPACE                         = 0x0020,  /* U+0020 SPACE */
    KC_EXCLAM                        = 0x0021,  /* U+0021 EXCLAMATION MARK */
    KC_QUOTEDBL                      = 0x0022,  /* U+0022 QUOTATION MARK */
    KC_NUMBERSIGN                    = 0x0023,  /* U+0023 NUMBER SIGN */
    KC_DOLLAR                        = 0x0024,  /* U+0024 DOLLAR SIGN */
    KC_PERCENT                       = 0x0025,  /* U+0025 PERCENT SIGN */
    KC_AMPERSAND                     = 0x0026,  /* U+0026 AMPERSAND */
    KC_APOSTROPHE                    = 0x0027,  /* U+0027 APOSTROPHE */
    KC_QUOTERIGHT                    = 0x0027,  /* deprecated */
    KC_PARENLEFT                     = 0x0028,  /* U+0028 LEFT PARENTHESIS */
    KC_PARENRIGHT                    = 0x0029,  /* U+0029 RIGHT PARENTHESIS */
    KC_ASTERISK                      = 0x002a,  /* U+002A ASTERISK */
    KC_PLUS                          = 0x002b,  /* U+002B PLUS SIGN */
    KC_COMMA                         = 0x002c,  /* U+002C COMMA */
    KC_MINUS                         = 0x002d,  /* U+002D HYPHEN-MINUS */
    KC_PERIOD                        = 0x002e,  /* U+002E FULL STOP */
    KC_SLASH                         = 0x002f,  /* U+002F SOLIDUS */
    KC_0                             = 0x0030,  /* U+0030 DIGIT ZERO */
    KC_1                             = 0x0031,  /* U+0031 DIGIT ONE */
    KC_2                             = 0x0032,  /* U+0032 DIGIT TWO */
    KC_3                             = 0x0033,  /* U+0033 DIGIT THREE */
    KC_4                             = 0x0034,  /* U+0034 DIGIT FOUR */
    KC_5                             = 0x0035,  /* U+0035 DIGIT FIVE */
    KC_6                             = 0x0036,  /* U+0036 DIGIT SIX */
    KC_7                             = 0x0037,  /* U+0037 DIGIT SEVEN */
    KC_8                             = 0x0038,  /* U+0038 DIGIT EIGHT */
    KC_9                             = 0x0039,  /* U+0039 DIGIT NINE */
    KC_COLON                         = 0x003a,  /* U+003A COLON */
    KC_SEMICOLON                     = 0x003b,  /* U+003B SEMICOLON */
    KC_LESS                          = 0x003c,  /* U+003C LESS-THAN SIGN */
    KC_EQUAL                         = 0x003d,  /* U+003D EQUALS SIGN */
    KC_GREATER                       = 0x003e,  /* U+003E GREATER-THAN SIGN */
    KC_QUESTION                      = 0x003f,  /* U+003F QUESTION MARK */
    KC_at                            = 0x0040,  /* U+0040 COMMERCIAL AT */
    KC_A                             = 0x0041,  /* U+0041 LATIN CAPITAL LETTER A */
    KC_B                             = 0x0042,  /* U+0042 LATIN CAPITAL LETTER B */
    KC_C                             = 0x0043,  /* U+0043 LATIN CAPITAL LETTER C */
    KC_D                             = 0x0044,  /* U+0044 LATIN CAPITAL LETTER D */
    KC_E                             = 0x0045,  /* U+0045 LATIN CAPITAL LETTER E */
    KC_F                             = 0x0046,  /* U+0046 LATIN CAPITAL LETTER F */
    KC_G                             = 0x0047,  /* U+0047 LATIN CAPITAL LETTER G */
    KC_H                             = 0x0048,  /* U+0048 LATIN CAPITAL LETTER H */
    KC_I                             = 0x0049,  /* U+0049 LATIN CAPITAL LETTER I */
    KC_J                             = 0x004a,  /* U+004A LATIN CAPITAL LETTER J */
    KC_K                             = 0x004b,  /* U+004B LATIN CAPITAL LETTER K */
    KC_L                             = 0x004c,  /* U+004C LATIN CAPITAL LETTER L */
    KC_M                             = 0x004d,  /* U+004D LATIN CAPITAL LETTER M */
    KC_N                             = 0x004e,  /* U+004E LATIN CAPITAL LETTER N */
    KC_O                             = 0x004f,  /* U+004F LATIN CAPITAL LETTER O */
    KC_P                             = 0x0050,  /* U+0050 LATIN CAPITAL LETTER P */
    KC_Q                             = 0x0051,  /* U+0051 LATIN CAPITAL LETTER Q */
    KC_R                             = 0x0052,  /* U+0052 LATIN CAPITAL LETTER R */
    KC_S                             = 0x0053,  /* U+0053 LATIN CAPITAL LETTER S */
    KC_T                             = 0x0054,  /* U+0054 LATIN CAPITAL LETTER T */
    KC_U                             = 0x0055,  /* U+0055 LATIN CAPITAL LETTER U */
    KC_V                             = 0x0056,  /* U+0056 LATIN CAPITAL LETTER V */
    KC_W                             = 0x0057,  /* U+0057 LATIN CAPITAL LETTER W */
    KC_X                             = 0x0058,  /* U+0058 LATIN CAPITAL LETTER X */
    KC_Y                             = 0x0059,  /* U+0059 LATIN CAPITAL LETTER Y */
    KC_Z                             = 0x005a,  /* U+005A LATIN CAPITAL LETTER Z */
    KC_BRACKETLEFT                   = 0x005b,  /* U+005B LEFT SQUARE BRACKET */
    KC_BACKSLASH                     = 0x005c,  /* U+005C REVERSE SOLIDUS */
    KC_BRACKETRIGHT                  = 0x005d,  /* U+005D RIGHT SQUARE BRACKET */
    KC_ASCIICIRCUM                   = 0x005e,  /* U+005E CIRCUMFLEX ACCENT */
    KC_UNDERSCORE                    = 0x005f,  /* U+005F LOW LINE */
    KC_GRAVE                         = 0x0060,  /* U+0060 GRAVE ACCENT */
    KC_QUOTELEFT                     = 0x0060,  /* deprecated */
    KC_BRACELEFT                     = 0x007b,  /* U+007B LEFT CURLY BRACKET */
    KC_BAR                           = 0x007c,  /* U+007C VERTICAL LINE */
    KC_BRACERIGHT                    = 0x007d,  /* U+007D RIGHT CURLY BRACKET */
    KC_ASCIITILDE                    = 0x007e,  /* U+007E TILDE */

    KC_NOBREAKSPACE                  = 0x00a0,  /* U+00A0 NO-BREAK SPACE */
    KC_EXCLAMDOWN                    = 0x00a1,  /* U+00A1 INVERTED EXCLAMATION MARK */
    KC_CENT                          = 0x00a2,  /* U+00A2 CENT SIGN */
    KC_STERLING                      = 0x00a3,  /* U+00A3 POUND SIGN */
    KC_CURRENCY                      = 0x00a4,  /* U+00A4 CURRENCY SIGN */
    KC_YEN                           = 0x00a5,  /* U+00A5 YEN SIGN */
    KC_BROKENBAR                     = 0x00a6,  /* U+00A6 BROKEN BAR */
    KC_SECTION                       = 0x00a7,  /* U+00A7 SECTION SIGN */
    KC_DIAERESIS                     = 0x00a8,  /* U+00A8 DIAERESIS */
    KC_COPYRIGHT                     = 0x00a9  /* U+00A9 COPYRIGHT SIGN */

};

#undef KMOD_CONTROL
#undef KMOD_SHIFT
#undef KMOD_ALT
#undef KMOD_GUI

enum KeyModifier
{
    KMOD_NONE = 0x0000,
    KMOD_SHIFT_L = 0x0001,
    KMOD_SHIFT_R = 0x0002,
    KMOD_CONTROL_L = 0x0040,
    KMOD_CONTROL_R = 0x0080,
    KMOD_ALT_L = 0x0100,
    KMOD_ALT_R = 0x0200,
    KMOD_GUI_L = 0x0400,
    KMOD_GUI_R = 0x0800,
    KMOD_NUM_LOCK = 0x1000,
    KMOD_CAPS_LOCK = 0x2000,
    KMOD_COMMAND = 0x4000,
    KMOD_RESERVED = 0x8000,
    KMOD_ANY = 0xffffffff,

    KMOD_CONTROL = (KMOD_CONTROL_L|KMOD_CONTROL_R),
    KMOD_SHIFT =   (KMOD_SHIFT_L|KMOD_SHIFT_R),
    KMOD_ALT =     (KMOD_ALT_L|KMOD_ALT_R),
    KMOD_GUI =     (KMOD_GUI_L|KMOD_GUI_R)
};


};

#endif
