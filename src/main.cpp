#include <windows.h>
#include <cstdio>
#include <psapi.h>
#include <thread>
#include "windows.h"
#include <vector>
#include <string>
#include "Controller.h"

using std::vector;
using std::string;


void test(const Controller &messages) {
    messages.sendKeyTap(KEY_A);
    Sleep(1000);
    messages.sendKeyTap(KEY_D);
    Sleep(1000);
    messages.sendKeyTap(KEY_A);
    Sleep(1000);
    messages.sendKeyTap(KEY_D);
    messages.sendKeyTap(KEY_W);
    Sleep(1000);
    messages.sendKeyTap(KEY_RETURN);
    Sleep(1000);
    messages.sendText("HEY");
    Sleep(1000);
    messages.sendText("hey!");
    Sleep(1000);
    messages.sendKeyTap(KEY_RETURN);

    //    typeText(childWindows, "THIS TEXT IS BEING TYPED ASYNCHRONOUSLY ON A BACKGROUND NOTEPAD WINDOW", hTimerQueue);
    //    Sleep(10000);
}



int main() {
    vector<HWND> windows = chooseWindows();
    Controller messages(windows);
    test(messages);
    return 0;
}