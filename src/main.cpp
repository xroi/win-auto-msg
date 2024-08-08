#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include <psapi.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <thread>

#define tapLengthMS 100

enum VKeys {
    KEY_0 = 0x30, //0 key
    KEY_1 = 0x31, //1 key
    KEY_2 = 0x32, //2 key
    KEY_3 = 0x33, //3 key
    KEY_4 = 0x34, //4 key
    KEY_5 = 0x35, //5 key
    KEY_6 = 0x36, //6 key
    KEY_7 = 0x37, //7 key
    KEY_8 = 0x38, //8 key
    KEY_9 = 0x39, //9 key
    KEY_MINUS = 0xBD, // - key
    KEY_PLUS = 0xBB, // + key
    KEY_A = 0x41, //A key
    KEY_B = 0x42, //B key
    KEY_C = 0x43, //C key
    KEY_D = 0x44, //D key
    KEY_E = 0x45, //E key
    KEY_F = 0x46, //F key
    KEY_G = 0x47, //G key
    KEY_H = 0x48, //H key
    KEY_I = 0x49, //I key
    KEY_J = 0x4A, //J key
    KEY_K = 0x4B, //K key
    KEY_L = 0x4C, //L key
    KEY_M = 0x4D, //M key
    KEY_N = 0x4E, //N key
    KEY_O = 0x4F, //O key
    KEY_P = 0x50, //P key
    KEY_Q = 0x51, //Q key
    KEY_R = 0x52, //R key
    KEY_S = 0x53, //S key
    KEY_T = 0x54, //T key
    KEY_U = 0x55, //U key
    KEY_V = 0x56, //V key
    KEY_W = 0x57, //W key
    KEY_X = 0x58, //X key
    KEY_Y = 0x59, //Y key
    KEY_Z = 0x5A, //Z key
    KEY_LBUTTON = 0x01, //Left mouse button
    KEY_RBUTTON = 0x02, //Right mouse button
    KEY_CANCEL = 0x03, //Control-break processing
    KEY_MBUTTON = 0x04, //Middle mouse button (three-button mouse)
    KEY_BACK = 0x08, //BACKSPACE key
    KEY_TAB = 0x09, //TAB key
    KEY_CLEAR = 0x0C, //CLEAR key
    KEY_RETURN = 0x0D, //ENTER key
    KEY_SHIFT = 0x10, //SHIFT key
    KEY_CONTROL = 0x11, //CTRL key
    KEY_MENU = 0x12, //ALT key
    KEY_PAUSE = 0x13, //PAUSE key
    KEY_CAPITAL = 0x14, //CAPS LOCK key
    KEY_ESCAPE = 0x1B, //ESC key
    KEY_SPACE = 0x20, //SPACEBAR
    KEY_PRIOR = 0x21, //PAGE UP key
    KEY_NEXT = 0x22, //PAGE DOWN key
    KEY_END = 0x23, //END key
    KEY_HOME = 0x24, //HOME key
    KEY_LEFT = 0x25, //LEFT ARROW key
    KEY_UP = 0x26, //UP ARROW key
    KEY_RIGHT = 0x27, //RIGHT ARROW key
    KEY_DOWN = 0x28, //DOWN ARROW key
    KEY_SELECT = 0x29, //SELECT key
    KEY_PRINT = 0x2A, //PRINT key
    _KEY_EXECUTE = 0x2B, //EXECUTE key
    KEY_SNAPSHOT = 0x2C, //PRINT SCREEN key
    KEY_INSERT = 0x2D, //INS key
    KEY_DELETE = 0x2E, //DEL key
    KEY_HELP = 0x2F, //HELP key
    KEY_NUMPAD0 = 0x60, //Numeric keypad 0 key
    KEY_NUMPAD1 = 0x61, //Numeric keypad 1 key
    KEY_NUMPAD2 = 0x62, //Numeric keypad 2 key
    KEY_NUMPAD3 = 0x63, //Numeric keypad 3 key
    KEY_NUMPAD4 = 0x64, //Numeric keypad 4 key
    KEY_NUMPAD5 = 0x65, //Numeric keypad 5 key
    KEY_NUMPAD6 = 0x66, //Numeric keypad 6 key
    KEY_NUMPAD7 = 0x67, //Numeric keypad 7 key
    KEY_NUMPAD8 = 0x68, //Numeric keypad 8 key
    KEY_NUMPAD9 = 0x69, //Numeric keypad 9 key
    KEY_SEPARATOR = 0x6C, //Separator key
    KEY_SUBTRACT = 0x6D, //Subtract key
    KEY_DECIMAL = 0x6E, //Decimal key
    KEY_DIVIDE = 0x6F, //Divide key
    KEY_F1 = 0x70, //F1 key
    KEY_F2 = 0x71, //F2 key
    KEY_F3 = 0x72, //F3 key
    KEY_F4 = 0x73, //F4 key
    KEY_F5 = 0x74, //F5 key
    KEY_F6 = 0x75, //F6 key
    KEY_F7 = 0x76, //F7 key
    KEY_F8 = 0x77, //F8 key
    KEY_F9 = 0x78, //F9 key
    KEY_F10 = 0x79, //F10 key
    KEY_F11 = 0x7A, //F11 key
    KEY_F12 = 0x7B, //F12 key
    KEY_SCROLL = 0x91, //SCROLL LOCK key
    KEY_LSHIFT = 0xA0, //Left SHIFT key
    KEY_RSHIFT = 0xA1, //Right SHIFT key
    KEY_LCONTROL = 0xA2, //Left CONTROL key
    KEY_RCONTROL = 0xA3, //Right CONTROL key
    KEY_LMENU = 0xA4, //Left MENU key
    KEY_RMENU = 0xA5, //Right MENU key
    KEY_COMMA = 0xBC, //, key
    KEY_PERIOD = 0xBE, //. key
    KEY_PLAY = 0xFA, //Play key
    KEY_ZOOM = 0xFB, //Zoom key
    _NULL = 0x0,
};

typedef std::pair<HWND, std::string> HwndTitlePair;
typedef std::vector<HwndTitlePair> HwndTitleVec;
struct HWNDkey {
    HWND hwnd;
    VKeys key;
};


bool uniquepred(const HwndTitlePair &l, const HwndTitlePair &r) {
    return l.first == r.first;
}

HwndTitleVec getSubWindows(HWND parent) {
    HwndTitleVec subWindows;
    EnumChildWindows(parent, [](HWND hwnd, LPARAM lParam) {
        auto *vec = reinterpret_cast<HwndTitleVec *>(lParam);
        int length = GetWindowTextLength(hwnd);
        char *title = new char[length + 1];
        GetWindowText(hwnd, title, length + 1);
        vec->emplace_back(hwnd, std::string(title));
        delete[] title;
        return TRUE;
    }, reinterpret_cast<LPARAM>(&subWindows));
    for (const auto &p: subWindows) {
        HwndTitleVec childSubWindows = getSubWindows(p.first);
        subWindows.insert(subWindows.end(), childSubWindows.begin(), childSubWindows.end());
    }
    std::sort(subWindows.begin(), subWindows.end()); // for unique
    subWindows.erase(std::unique(subWindows.begin(), subWindows.end(), uniquepred), subWindows.end());
    return subWindows;
}

HwndTitleVec getAllWindows() {
    HwndTitleVec vec = {};
    for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) {
        if (!IsWindowVisible(hwnd))
            continue;
        int length = GetWindowTextLength(hwnd);
        if (length == 0)
            continue;
        char *title = new char[length + 1];
        GetWindowText(hwnd, title, length + 1);
        if (!strcmp("This PC", title)) {
            continue;
        }
        if (!strcmp("Tools", title)) {
            continue;
        }
        vec.emplace_back(hwnd, std::string(title));
    }
    std::sort(vec.begin(), vec.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });
    return vec;
}


LPARAM GetLParam(UINT repeatCount, UINT key, byte extended, byte contextCode, byte previousState,
                 byte transitionState) {
    LPARAM lParam = repeatCount;
    UINT scanCode = MapVirtualKey((UINT) key, MAPVK_VK_TO_CHAR);
    lParam += (UINT) scanCode * 0x10000;
    lParam += (UINT) ((extended) * 0x1000000);
    lParam += (UINT) ((contextCode * 2) * 0x10000000);
    lParam += (UINT) ((previousState * 4) * 0x10000000);
    lParam += (UINT) ((transitionState * 8) * 0x10000000);
    return lParam;
}

//void sendKeyTap(HwndTitleVec &hwnds, VKeys key) {
//    for (const auto &p: hwnds) {
//        int ret = PostMessage(p.first, WM_KEYDOWN, key, GetLParam(1, key, 0, 0, 0, 0));
//        std::cout << ret;
//        Sleep(1000);
//        PostMessage(p.first, WM_KEYUP, key, GetLParam(1, key, 0, 0, 1, 1));
//    }
//}

void CALLBACK endKeyPress(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
    auto *hwndKey = (HWNDkey *) lpParam;
    std::cout << "Timer triggered" << std::endl;
    PostMessage(hwndKey->hwnd, WM_KEYUP, hwndKey->key, GetLParam(1, hwndKey->key, 0, 0, 1, 1));
    delete (HWNDkey *) lpParam;
}

int initiateKeyPress(HWND hwnd, VKeys key, HANDLE hTimerQueue, DWORD lengthMS) {
    int ret = PostMessage(hwnd, WM_KEYDOWN, key, GetLParam(1, key, 0, 0, 0, 0));
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;
    auto *hwndKey = new HWNDkey{hwnd, key};
    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, endKeyPress, hwndKey, lengthMS, 0, 0)) {
        printf("CreateTimerQueueTimer failed (%d)\n", GetLastError());
        return 1;
    }
    std::cout << "SetWaitableTimer sucess" << std::endl;
    return 0;
}

void sendKeyTap(HwndTitleVec &hwnds, VKeys key, HANDLE hTimerQueue) {
    for (const auto &p: hwnds) {
        initiateKeyPress(p.first, key, hTimerQueue, tapLengthMS);
    }
}

void typeText(HwndTitleVec &hwnds, std::string text, HANDLE hTimerQueue) {
    for (char &c: text) {
        sendKeyTap(hwnds, (VKeys) c, hTimerQueue);
    }
}

int main() {
    HANDLE hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue) {
        printf("CreateTimerQueue failed (%d)\n", GetLastError());
        return 0;
    }
    HwndTitleVec topWindowsVec = getAllWindows();
    int i = 0;
    for (const auto &p: topWindowsVec) {
        std::cout << i << ": " << p.second << " " << p.first << std::endl;
        i++;
        HwndTitleVec subWindowsVec = getSubWindows(p.first);
//        for (const auto &p2: subWindowsVec) {
//            std::cout << "\t" << p2.second << " " << p2.first << std::endl;
//        }
    }
    std::cout << "Please choose a window." << std::endl;
    int ind;
    std::cin >> ind;
    HwndTitleVec subWindows = getSubWindows(topWindowsVec[ind].first);
    subWindows.push_back(topWindowsVec[ind]);
//    sendKeyTap(subWindows, KEY_A, hTimerQueue);
//    Sleep(1000);
//    sendKeyTap(subWindows, KEY_D, hTimerQueue);
//    Sleep(1000);
//    sendKeyTap(subWindows, KEY_A, hTimerQueue);
//    Sleep(1000);
//    sendKeyTap(subWindows, KEY_D, hTimerQueue);
//    sendKeyTap(subWindows, KEY_W, hTimerQueue);
//    Sleep(1000);
    typeText(subWindows, "THIS TEXT IS BEING TYPED ASYNCHRONOUSLY ON A BACKGROUND NOTEPAD WINDOW", hTimerQueue);
    Sleep(10000);
    if (!DeleteTimerQueue(hTimerQueue))
        printf("DeleteTimerQueue failed (%d)\n", GetLastError());
    return 0;
}