//
// Created by roi65 on Thu 15/08/2024.
//

#ifndef AUTO_WIN_MSG_VKEY_HPP
#define AUTO_WIN_MSG_VKEY_HPP

#include <unordered_map>
#include <optional>

enum VKey {
    // Mouse buttons
    KEY_LBUTTON = 0x01,       // Left mouse button
    KEY_RBUTTON = 0x02,       // Right mouse button
    KEY_CANCEL = 0x03,        // Control-break processing
    KEY_MBUTTON = 0x04,       // Middle mouse button (three-button mouse)
    KEY_XBUTTON1 = 0x05,      // X1 mouse button
    KEY_XBUTTON2 = 0x06,      // X2 mouse button

    // Keyboard control keys
    KEY_BACK = 0x08,          // BACKSPACE key
    KEY_TAB = 0x09,           // TAB key
    KEY_CLEAR = 0x0C,         // CLEAR key
    KEY_RETURN = 0x0D,        // ENTER key
    KEY_SHIFT = 0x10,         // SHIFT key
    KEY_CONTROL = 0x11,       // CTRL key
    KEY_MENU = 0x12,          // ALT key
    KEY_PAUSE = 0x13,         // PAUSE key
    KEY_CAPITAL = 0x14,       // CAPS LOCK key
    KEY_ESCAPE = 0x1B,        // ESC key
    KEY_SPACE = 0x20,         // SPACEBAR

    // Navigation keys
    KEY_PRIOR = 0x21,         // PAGE UP key
    KEY_NEXT = 0x22,          // PAGE DOWN key
    KEY_END = 0x23,           // END key
    KEY_HOME = 0x24,          // HOME key
    KEY_LEFT = 0x25,          // LEFT ARROW key
    KEY_UP = 0x26,            // UP ARROW key
    KEY_RIGHT = 0x27,         // RIGHT ARROW key
    KEY_DOWN = 0x28,          // DOWN ARROW key

    // Other control keys
    KEY_SELECT = 0x29,        // SELECT key
    KEY_PRINT = 0x2A,         // PRINT key
//    KEY_EXECUTE = 0x2B,       // EXECUTE key
    KEY_SNAPSHOT = 0x2C,      // PRINT SCREEN key
    KEY_INSERT = 0x2D,        // INS key
    KEY_DELETE = 0x2E,        // DEL key
    KEY_HELP = 0x2F,          // HELP key

    // Number keys
    KEY_0 = 0x30,             // 0 key
    KEY_1 = 0x31,             // 1 key
    KEY_2 = 0x32,             // 2 key
    KEY_3 = 0x33,             // 3 key
    KEY_4 = 0x34,             // 4 key
    KEY_5 = 0x35,             // 5 key
    KEY_6 = 0x36,             // 6 key
    KEY_7 = 0x37,             // 7 key
    KEY_8 = 0x38,             // 8 key
    KEY_9 = 0x39,             // 9 key

    // Alphabet keys
    KEY_A = 0x41,             // A key
    KEY_B = 0x42,             // B key
    KEY_C = 0x43,             // C key
    KEY_D = 0x44,             // D key
    KEY_E = 0x45,             // E key
    KEY_F = 0x46,             // F key
    KEY_G = 0x47,             // G key
    KEY_H = 0x48,             // H key
    KEY_I = 0x49,             // I key
    KEY_J = 0x4A,             // J key
    KEY_K = 0x4B,             // K key
    KEY_L = 0x4C,             // L key
    KEY_M = 0x4D,             // M key
    KEY_N = 0x4E,             // N key
    KEY_O = 0x4F,             // O key
    KEY_P = 0x50,             // P key
    KEY_Q = 0x51,             // Q key
    KEY_R = 0x52,             // R key
    KEY_S = 0x53,             // S key
    KEY_T = 0x54,             // T key
    KEY_U = 0x55,             // U key
    KEY_V = 0x56,             // V key
    KEY_W = 0x57,             // W key
    KEY_X = 0x58,             // X key
    KEY_Y = 0x59,             // Y key
    KEY_Z = 0x5A,             // Z key

    // Numpad keys
    KEY_NUMPAD0 = 0x60,       // Numeric keypad 0 key
    KEY_NUMPAD1 = 0x61,       // Numeric keypad 1 key
    KEY_NUMPAD2 = 0x62,       // Numeric keypad 2 key
    KEY_NUMPAD3 = 0x63,       // Numeric keypad 3 key
    KEY_NUMPAD4 = 0x64,       // Numeric keypad 4 key
    KEY_NUMPAD5 = 0x65,       // Numeric keypad 5 key
    KEY_NUMPAD6 = 0x66,       // Numeric keypad 6 key
    KEY_NUMPAD7 = 0x67,       // Numeric keypad 7 key
    KEY_NUMPAD8 = 0x68,       // Numeric keypad 8 key
    KEY_NUMPAD9 = 0x69,       // Numeric keypad 9 key

    // Numpad operation keys
    KEY_MULTIPLY = 0x6A,      // Multiply key
    KEY_ADD = 0x6B,           // Add key
    KEY_SEPARATOR = 0x6C,     // Separator key
    KEY_SUBTRACT = 0x6D,      // Subtract key
    KEY_DECIMAL = 0x6E,       // Decimal key
    KEY_DIVIDE = 0x6F,        // Divide key

    // Function keys
    KEY_F1 = 0x70,            // F1 key
    KEY_F2 = 0x71,            // F2 key
    KEY_F3 = 0x72,            // F3 key
    KEY_F4 = 0x73,            // F4 key
    KEY_F5 = 0x74,            // F5 key
    KEY_F6 = 0x75,            // F6 key
    KEY_F7 = 0x76,            // F7 key
    KEY_F8 = 0x77,            // F8 key
    KEY_F9 = 0x78,            // F9 key
    KEY_F10 = 0x79,           // F10 key
    KEY_F11 = 0x7A,           // F11 key
    KEY_F12 = 0x7B,           // F12 key
    KEY_F13 = 0x7C,           // F13 key
    KEY_F14 = 0x7D,           // F14 key
    KEY_F15 = 0x7E,           // F15 key
    KEY_F16 = 0x7F,           // F16 key
    KEY_F17 = 0x80,           // F17 key
    KEY_F18 = 0x81,           // F18 key
    KEY_F19 = 0x82,           // F19 key
    KEY_F20 = 0x83,           // F20 key
    KEY_F21 = 0x84,           // F21 key
    KEY_F22 = 0x85,           // F22 key
    KEY_F23 = 0x86,           // F23 key
    KEY_F24 = 0x87,           // F24 key

    // Lock keys
    KEY_NUMLOCK = 0x90,       // NUM LOCK key
    KEY_SCROLL = 0x91,        // SCROLL LOCK key

    // Left/Right modifier keys
    KEY_LSHIFT = 0xA0,        // Left SHIFT key
    KEY_RSHIFT = 0xA1,        // Right SHIFT key
    KEY_LCONTROL = 0xA2,      // Left CONTROL key
    KEY_RCONTROL = 0xA3,      // Right CONTROL key
    KEY_LMENU = 0xA4,         // Left MENU (ALT) key
    KEY_RMENU = 0xA5,         // Right MENU (ALT) key

    // OEM specific keys
    KEY_OEM_1 = 0xBA,         // ';:' key
    KEY_OEM_PLUS = 0xBB,      // '+' key
    KEY_OEM_COMMA = 0xBC,     // ',' key
    KEY_OEM_MINUS = 0xBD,     // '-' key
    KEY_OEM_PERIOD = 0xBE,    // '.' key
    KEY_OEM_2 = 0xBF,         // '/?' key
    KEY_OEM_3 = 0xC0,         // '`~' key
    KEY_OEM_4 = 0xDB,         // '[{' key
    KEY_OEM_5 = 0xDC,         // '\|' key
    KEY_OEM_6 = 0xDD,         // ']}' key
    KEY_OEM_7 = 0xDE,         // ''"' key
    KEY_OEM_8 = 0xDF,         // Various language-specific keys

    // Additional media and special keys
    KEY_PLAY = 0xFA,          // Play key
    KEY_ZOOM = 0xFB,          // Zoom key

    // Null key
    KEY_NULL = 0x00           // Null/undefined key
};


// Struct to represent a key mapping with potential shift state
struct VKeyMapping {
    VKey key;          // The primary key
    bool requiresShift; // Whether shift key is needed

    VKeyMapping(VKey k, bool shift = false)
            : key(k), requiresShift(shift) {}
};

const std::unordered_map<char, VKeyMapping> CharToVKeyMap = {
        // Numbers (without shift)
        {'0', {VKey::KEY_0, false}},
        {'1', {VKey::KEY_1, false}},
        {'2', {VKey::KEY_2, false}},
        {'3', {VKey::KEY_3, false}},
        {'4', {VKey::KEY_4, false}},
        {'5', {VKey::KEY_5, false}},
        {'6', {VKey::KEY_6, false}},
        {'7', {VKey::KEY_7, false}},
        {'8', {VKey::KEY_8, false}},
        {'9', {VKey::KEY_9, false}},

        // Lowercase letters
        {'a', {VKey::KEY_A, false}},
        {'b', {VKey::KEY_B, false}},
        {'c', {VKey::KEY_C, false}},
        {'d', {VKey::KEY_D, false}},
        {'e', {VKey::KEY_E, false}},
        {'f', {VKey::KEY_F, false}},
        {'g', {VKey::KEY_G, false}},
        {'h', {VKey::KEY_H, false}},
        {'i', {VKey::KEY_I, false}},
        {'j', {VKey::KEY_J, false}},
        {'k', {VKey::KEY_K, false}},
        {'l', {VKey::KEY_L, false}},
        {'m', {VKey::KEY_M, false}},
        {'n', {VKey::KEY_N, false}},
        {'o', {VKey::KEY_O, false}},
        {'p', {VKey::KEY_P, false}},
        {'q', {VKey::KEY_Q, false}},
        {'r', {VKey::KEY_R, false}},
        {'s', {VKey::KEY_S, false}},
        {'t', {VKey::KEY_T, false}},
        {'u', {VKey::KEY_U, false}},
        {'v', {VKey::KEY_V, false}},
        {'w', {VKey::KEY_W, false}},
        {'x', {VKey::KEY_X, false}},
        {'y', {VKey::KEY_Y, false}},
        {'z', {VKey::KEY_Z, false}},

        // Uppercase letters (with shift)
        {'A', {VKey::KEY_A, true}},
        {'B', {VKey::KEY_B, true}},
        {'C', {VKey::KEY_C, true}},
        {'D', {VKey::KEY_D, true}},
        {'E', {VKey::KEY_E, true}},
        {'F', {VKey::KEY_F, true}},
        {'G', {VKey::KEY_G, true}},
        {'H', {VKey::KEY_H, true}},
        {'I', {VKey::KEY_I, true}},
        {'J', {VKey::KEY_J, true}},
        {'K', {VKey::KEY_K, true}},
        {'L', {VKey::KEY_L, true}},
        {'M', {VKey::KEY_M, true}},
        {'N', {VKey::KEY_N, true}},
        {'O', {VKey::KEY_O, true}},
        {'P', {VKey::KEY_P, true}},
        {'Q', {VKey::KEY_Q, true}},
        {'R', {VKey::KEY_R, true}},
        {'S', {VKey::KEY_S, true}},
        {'T', {VKey::KEY_T, true}},
        {'U', {VKey::KEY_U, true}},
        {'V', {VKey::KEY_V, true}},
        {'W', {VKey::KEY_W, true}},
        {'X', {VKey::KEY_X, true}},
        {'Y', {VKey::KEY_Y, true}},
        {'Z', {VKey::KEY_Z, true}},

        // Symbols (some require shift)
        {'`', {VKey::KEY_OEM_3, false}},          // Backtick/Tilde
        {'~', {VKey::KEY_OEM_3, true}},    // Tilde (shifted)
        {'-', {VKey::KEY_OEM_MINUS, false}},           // Hyphen/Minus
        {'_', {VKey::KEY_OEM_MINUS, true}},     // Underscore (shifted)
        {'=', {VKey::KEY_OEM_PLUS, false}},            // Equals
        {'+', {VKey::KEY_OEM_PLUS, true}},      // Plus (shifted)
        {'[', {VKey::KEY_OEM_4, false}},           // Left bracket
        {'{', {VKey::KEY_OEM_4, true}},     // Left brace (shifted)
        {']', {VKey::KEY_OEM_6, false}},           // Right bracket
        {'}', {VKey::KEY_OEM_6, true}},     // Right brace (shifted)
        {';', {VKey::KEY_OEM_1, false}},           // Semicolon
        {':', {VKey::KEY_OEM_1, true}},     // Colon (shifted)
        {'\'', {VKey::KEY_OEM_7, false}},          // Single quote
        {'"', {VKey::KEY_OEM_7, true}},     // Double quote (shifted)
        {'\\', {VKey::KEY_OEM_5, false}},          // Backslash
        {'|', {VKey::KEY_OEM_5, true}},     // Pipe (shifted)
        {',', {VKey::KEY_OEM_COMMA, false}},           // Comma
        {'<', {VKey::KEY_OEM_COMMA, true}},     // Less than (shifted)
        {'.', {VKey::KEY_OEM_PERIOD, false}},          // Period
        {'>', {VKey::KEY_OEM_PERIOD, true}},    // Greater than (shifted)
        {'/', {VKey::KEY_OEM_2, false}},           // Forward slash
        {'?', {VKey::KEY_OEM_2, true}},     // Question mark (shifted)

        // Number row symbols (shifted)
        {'!', {VKey::KEY_1, true}},
        {'@', {VKey::KEY_2, true}},
        {'#', {VKey::KEY_3, true}},
        {'$', {VKey::KEY_4, true}},
        {'%', {VKey::KEY_5, true}},
        {'^', {VKey::KEY_6, true}},
        {'&', {VKey::KEY_7, true}},
        {'*', {VKey::KEY_8, true}},
        {'(', {VKey::KEY_9, true}},
        {')', {VKey::KEY_0, true}},

        // Other special keys
        {' ', {VKey::KEY_SPACE, false}}
};

#endif //AUTO_WIN_MSG_VKEY_HPP
