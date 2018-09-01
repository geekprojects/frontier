
static const KeyCode g_darwinKeyCodeMap[] = {
    /*   0 */   KC_A,
    /*   1 */   KC_S,
    /*   2 */   KC_D,
    /*   3 */   KC_F,
    /*   4 */   KC_H,
    /*   5 */   KC_G,
    /*   6 */   KC_Z,
    /*   7 */   KC_X,
    /*   8 */   KC_C,
    /*   9 */   KC_V,
    /*  10 */   KC_BACKSLASH, /* KC_NONUSBACKSLASH on ANSI and JIS keyboards (if this key would exist there), KC_GRAVE on ISO. (The USB keyboard driver actually translates these usage codes to different virtual key codes depending on whether the keyboard is ISO/ANSI/JIS. That's why you have to help it identify the keyboard type when you plug in a PC USB keyboard. It's a historical thing - ADB keyboards are wired this way.) */
    /*  11 */   KC_B,
    /*  12 */   KC_Q,
    /*  13 */   KC_W,
    /*  14 */   KC_E,
    /*  15 */   KC_R,
    /*  16 */   KC_Y,
    /*  17 */   KC_T,
    /*  18 */   KC_1,
    /*  19 */   KC_2,
    /*  20 */   KC_3,
    /*  21 */   KC_4,
    /*  22 */   KC_6,
    /*  23 */   KC_5,
    /*  24 */   KC_EQUAL,
    /*  25 */   KC_9,
    /*  26 */   KC_7,
    /*  27 */   KC_MINUS,
    /*  28 */   KC_8,
    /*  29 */   KC_0,
    /*  30 */   KC_BRACKETRIGHT,
    /*  31 */   KC_O,
    /*  32 */   KC_U,
    /*  33 */   KC_BRACKETLEFT,
    /*  34 */   KC_I,
    /*  35 */   KC_P,
    /*  36 */   KC_RETURN,
    /*  37 */   KC_L,
    /*  38 */   KC_J,
    /*  39 */   KC_APOSTROPHE,
    /*  40 */   KC_K,
    /*  41 */   KC_SEMICOLON,
    /*  42 */   KC_BACKSLASH,
    /*  43 */   KC_COMMA,
    /*  44 */   KC_SLASH,
    /*  45 */   KC_N,
    /*  46 */   KC_M,
    /*  47 */   KC_PERIOD,
    /*  48 */   KC_TAB,
    /*  49 */   KC_SPACE,
    /*  50 */   KC_GRAVE, /* KC_GRAVE on ANSI and JIS keyboards, KC_NONUSBACKSLASH on ISO (see comment about virtual key code 10 above) */
    /*  51 */   KC_BACKSPACE,
    /*  52 */   KC_KP_ENTER, /* keyboard enter on portables */
    /*  53 */   KC_ESCAPE,
    /*  54 */   KC_UNKNOWN, //KC_RGUI,
    /*  55 */   KC_UNKNOWN, //KC_LGUI,
    /*  56 */   KC_SHIFT_L,
    /*  57 */   KC_CAPS_LOCK,
    /*  58 */   KC_ALT_L,
    /*  59 */   KC_CONTROL_L,
    /*  60 */   KC_SHIFT_R,
    /*  61 */   KC_ALT_R,
    /*  62 */   KC_CONTROL_R,
    /*  63 */   KC_UNKNOWN, //KC_RGUI, /* fn on portables, acts as a hardware-level modifier already, so we don't generate events for it, also XK_Meta_R */
    /*  64 */   KC_F17,
    /*  65 */   KC_PERIOD,
    /*  66 */   KC_UNKNOWN, /* unknown (unused?) */
    /*  67 */   KC_KP_MULTIPLY,
    /*  68 */   KC_UNKNOWN, /* unknown (unused?) */
    /*  69 */   KC_KP_ADD,
    /*  70 */   KC_UNKNOWN, /* unknown (unused?) */
    /*  71 */   KC_NUM_LOCK,
    /*  72 */   KC_UNKNOWN, //KC_VOLUMEUP,
    /*  73 */   KC_UNKNOWN, //KC_VOLUMEDOWN,
    /*  74 */   KC_UNKNOWN, //KC_MUTE,
    /*  75 */   KC_KP_DIVIDE,
    /*  76 */   KC_KP_ENTER, /* keypad enter on external keyboards, fn-return on portables */
    /*  77 */   KC_UNKNOWN, /* unknown (unused?) */
    /*  78 */   KC_KP_SUBTRACT,
    /*  79 */   KC_F18,
    /*  80 */   KC_F19,
    /*  81 */   KC_KP_EQUAL,
    /*  82 */   KC_KP_0,
    /*  83 */   KC_KP_1,
    /*  84 */   KC_KP_2,
    /*  85 */   KC_KP_3,
    /*  86 */   KC_KP_4,
    /*  87 */   KC_KP_5,
    /*  88 */   KC_KP_6,
    /*  89 */   KC_KP_7,
    /*  90 */   KC_UNKNOWN, /* unknown (unused?) */
    /*  91 */   KC_KP_8,
    /*  92 */   KC_KP_9,
    /*  93 */   KC_YEN, /* Cosmo_USB2ADB.c says "Yen (JIS)" */
    /*  94 */   KC_UNKNOWN, //KC_INTERNATIONAL1, /* Cosmo_USB2ADB.c says "Ro (JIS)" */
    /*  95 */   KC_KP_COMMA, /* Cosmo_USB2ADB.c says ", JIS only" */
    /*  96 */   KC_F5,
    /*  97 */   KC_F6,
    /*  98 */   KC_F7,
    /*  99 */   KC_F3,
    /* 100 */   KC_F8,
    /* 101 */   KC_F9,
    /* 102 */   KC_UNKNOWN, //KC_LANG2, /* Cosmo_USB2ADB.c says "Eisu" */
    /* 103 */   KC_F11,
    /* 104 */   KC_UNKNOWN, //KC_LANG1, /* Cosmo_USB2ADB.c says "Kana" */
    /* 105 */   KC_PRINT_SCREEN, /* On ADB keyboards, this key is labeled "F13/print screen". Problem: USB has different usage codes for these two functions. On Apple USB keyboards, the key is labeled "F13" and sends the F13 usage code (KC_F13). I decided to use KC_PRINTSCREEN here nevertheless since SDL applications are more likely to assume the presence of a print screen key than an F13 key. */
    /* 106 */   KC_F16,
    /* 107 */   KC_SCROLL_LOCK, /* F14/scroll lock, see comment about F13/print screen above */
    /* 108 */   KC_UNKNOWN, /* unknown (unused?) */
    /* 109 */   KC_F10,
    /* 110 */   KC_UNKNOWN, //KC_APPLICATION, /* windows contextual menu key, fn-enter on portables */
    /* 111 */   KC_F12,
    /* 112 */   KC_UNKNOWN, /* unknown (unused?) */
    /* 113 */   KC_PAUSE, /* F15/pause, see comment about F13/print screen above */
    /* 114 */   KC_INSERT, /* the key is actually labeled "help" on Apple keyboards, and works as such in Mac OS, but it sends the "insert" usage code even on Apple USB keyboards */
    /* 115 */   KC_HOME,
    /* 116 */   KC_PAGE_UP,
    /* 117 */   KC_DELETE,
    /* 118 */   KC_F4,
    /* 119 */   KC_END,
    /* 120 */   KC_F2,
    /* 121 */   KC_PAGE_DOWN,
    /* 122 */   KC_F1,
    /* 123 */   KC_LEFT,
    /* 124 */   KC_RIGHT,
    /* 125 */   KC_DOWN,
    /* 126 */   KC_UP,
    /* 127 */   KC_UNKNOWN, //KC_POWER
};
/* *INDENT-ON* */
