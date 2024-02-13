﻿#pragma once

enum
{
    CC_KEYCODE_A = 4,
    CC_KEYCODE_B = 5,
    CC_KEYCODE_C = 6,
    CC_KEYCODE_D = 7,
    CC_KEYCODE_E = 8,
    CC_KEYCODE_F = 9,
    CC_KEYCODE_G = 10,
    CC_KEYCODE_H = 11,
    CC_KEYCODE_I = 12,
    CC_KEYCODE_J = 13,
    CC_KEYCODE_K = 14,
    CC_KEYCODE_L = 15,
    CC_KEYCODE_M = 16,
    CC_KEYCODE_N = 17,
    CC_KEYCODE_O = 18,
    CC_KEYCODE_P = 19,
    CC_KEYCODE_Q = 20,
    CC_KEYCODE_R = 21,
    CC_KEYCODE_S = 22,
    CC_KEYCODE_T = 23,
    CC_KEYCODE_U = 24,
    CC_KEYCODE_V = 25,
    CC_KEYCODE_W = 26,
    CC_KEYCODE_X = 27,
    CC_KEYCODE_Y = 28,
    CC_KEYCODE_Z = 29,
    CC_KEYCODE_1 = 30,
    CC_KEYCODE_2 = 31,
    CC_KEYCODE_3 = 32,
    CC_KEYCODE_4 = 33,
    CC_KEYCODE_5 = 34,
    CC_KEYCODE_6 = 35,
    CC_KEYCODE_7 = 36,
    CC_KEYCODE_8 = 37,
    CC_KEYCODE_9 = 38,
    CC_KEYCODE_0 = 39,
    CC_KEYCODE_RETURN = 40,
    CC_KEYCODE_ESCAPE = 41,
    CC_KEYCODE_BACKSPACE = 42,
    CC_KEYCODE_TAB = 43,
    CC_KEYCODE_SPACE = 44,
    CC_KEYCODE_MINUS = 45,
    CC_KEYCODE_EQUALS = 46,
    CC_KEYCODE_LEFTBRACKET = 47,
    CC_KEYCODE_RIGHTBRACKET = 48,
    CC_KEYCODE_BACKSLASH = 49,
    CC_KEYCODE_NONUSHASH = 50,
    CC_KEYCODE_SEMICOLON = 51,
    CC_KEYCODE_APOSTROPHE = 52,
    CC_KEYCODE_GRAVE = 53,
    CC_KEYCODE_COMMA = 54,
    CC_KEYCODE_PERIOD = 55,
    CC_KEYCODE_SLASH = 56,
    CC_KEYCODE_CAPSLOCK = 57,
    CC_KEYCODE_F1 = 58,
    CC_KEYCODE_F2 = 59,
    CC_KEYCODE_F3 = 60,
    CC_KEYCODE_F4 = 61,
    CC_KEYCODE_F5 = 62,
    CC_KEYCODE_F6 = 63,
    CC_KEYCODE_F7 = 64,
    CC_KEYCODE_F8 = 65,
    CC_KEYCODE_F9 = 66,
    CC_KEYCODE_F10 = 67,
    CC_KEYCODE_F11 = 68,
    CC_KEYCODE_F12 = 69,
    CC_KEYCODE_PRINTSCREEN = 70,
    CC_KEYCODE_SCROLLLOCK = 71,
    CC_KEYCODE_PAUSE = 72,
    CC_KEYCODE_INSERT = 73,
    CC_KEYCODE_HOME = 74,
    CC_KEYCODE_PAGEUP = 75,
    CC_KEYCODE_DELETE = 76,
    CC_KEYCODE_END = 77,
    CC_KEYCODE_PAGEDOWN = 78,
    CC_KEYCODE_RIGHT = 79,
    CC_KEYCODE_LEFT = 80,
    CC_KEYCODE_DOWN = 81,
    CC_KEYCODE_UP = 82,
    CC_KEYCODE_NUMLOCKCLEAR = 83,
    CC_KEYCODE_KP_DIVIDE = 84,
    CC_KEYCODE_KP_MULTIPLY = 85,
    CC_KEYCODE_KP_MINUS = 86,
    CC_KEYCODE_KP_PLUS = 87,
    CC_KEYCODE_KP_ENTER = 88,
    CC_KEYCODE_KP_1 = 89,
    CC_KEYCODE_KP_2 = 90,
    CC_KEYCODE_KP_3 = 91,
    CC_KEYCODE_KP_4 = 92,
    CC_KEYCODE_KP_5 = 93,
    CC_KEYCODE_KP_6 = 94,
    CC_KEYCODE_KP_7 = 95,
    CC_KEYCODE_KP_8 = 96,
    CC_KEYCODE_KP_9 = 97,
    CC_KEYCODE_KP_0 = 98,
    CC_KEYCODE_KP_PERIOD = 99,
    CC_KEYCODE_NONUSBACKSLASH = 100,
    CC_KEYCODE_APPLICATION = 101,
    CC_KEYCODE_POWER = 102,
    CC_KEYCODE_KP_EQUALS = 103,
    CC_KEYCODE_F13 = 104,
    CC_KEYCODE_F14 = 105,
    CC_KEYCODE_F15 = 106,
    CC_KEYCODE_F16 = 107,
    CC_KEYCODE_F17 = 108,
    CC_KEYCODE_F18 = 109,
    CC_KEYCODE_F19 = 110,
    CC_KEYCODE_F20 = 111,
    CC_KEYCODE_F21 = 112,
    CC_KEYCODE_F22 = 113,
    CC_KEYCODE_F23 = 114,
    CC_KEYCODE_F24 = 115,
    CC_KEYCODE_EXECUTE = 116,
    CC_KEYCODE_HELP = 117,
    CC_KEYCODE_MENU = 118,
    CC_KEYCODE_SELECT = 119,
    CC_KEYCODE_STOP = 120,
    CC_KEYCODE_AGAIN = 121,
    CC_KEYCODE_UNDO = 122,
    CC_KEYCODE_CUT = 123,
    CC_KEYCODE_COPY = 124,
    CC_KEYCODE_PASTE = 125,
    CC_KEYCODE_FIND = 126,
    CC_KEYCODE_MUTE = 127,
    CC_KEYCODE_VOLUMEUP = 128,
    CC_KEYCODE_VOLUMEDOWN = 129,
    CC_KEYCODE_LCTRL = 224,
    CC_KEYCODE_LSHIFT = 225,
    CC_KEYCODE_LALT = 226,
    CC_KEYCODE_LGUI = 227,
    CC_KEYCODE_RCTRL = 228,
    CC_KEYCODE_RSHIFT = 229,
    CC_KEYCODE_RALT = 230,
    CC_KEYCODE_RGUI = 231
};

enum CC_KeyCode
{
    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,
    Alpha1 = 30,
    Alpha2 = 31,
    Alpha3 = 32,
    Alpha4 = 33,
    Alpha5 = 34,
    Alpha6 = 35,
    Alpha7 = 36,
    Alpha8 = 37,
    Alpha9 = 38,
    Alpha0 = 39,
    Return = 40,
    EscapeKey = 41,
    Backspace = 42,
    Tab = 43,
    Space = 44,
    Minus = 45,
    Equals = 46,
    LeftBracket = 47,
    RightBracket = 48,
    Backslash = 49,
    NonUsHash = 50,
    Semicolon = 51,
    Apostrophe = 52,
    Grave = 53,
    Comma = 54,
    Period = 55,
    Slash = 56,
    Capslock = 57,
    F1 = 58,
    F2 = 59,
    F3 = 60,
    F4 = 61,
    F5 = 62,
    F6 = 63,
    F7 = 64,
    F8 = 65,
    F9 = 66,
    F10 = 67,
    F11 = 68,
    F12 = 69,
    PrintScreen = 70,
    ScrollLock = 71,
    Pause = 72,
    Insert = 73,
    Home = 74,
    PageUp = 75,
    Delete = 76,
    End = 77,
    PageDown = 78,
    Right = 79,
    Left = 80,
    Down = 81,
    Up = 82,
    NumLockClear = 83,
    KP_Divide = 84,
    KP_Multiply = 85,
    KP_Minus = 86,
    KP_Plus = 87,
    KP_Enter = 88,
    KP_1 = 89,
    KP_2 = 90,
    KP_3 = 91,
    KP_4 = 92,
    KP_5 = 93,
    KP_6 = 94,
    KP_7 = 95,
    KP_8 = 96,
    KP_9 = 97,
    KP_0 = 98,
    KP_Period = 99,
    NonUsBackslash = 100,
    ApplicationKey = 101,
    Power = 102,
    KP_Equals = 103,
    F13 = 104,
    F14 = 105,
    F15 = 106,
    F16 = 107,
    F17 = 108,
    F18 = 109,
    F19 = 110,
    F20 = 111,
    F21 = 112,
    F22 = 113,
    F23 = 114,
    F24 = 115,
    Execute = 116,
    Help = 117,
    Menu = 118,
    Select = 119,
    Stop = 120,
    Again = 121,
    Undo = 122,
    Cut = 123,
    Copy = 124,
    Paste = 125,
    Find = 126,
    Mute = 127,
    VolumeUp = 128,
    VolumeDown = 129,
    LCtrl = 224,
    LShift = 225,
    LAlt = 226,
    LGUI = 227,
    RCtrl = 228,
    RShift = 229,
    RAlt = 230,
    RGUI = 231
};
