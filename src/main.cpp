#include <windows.h>
#include <cstdio>
#include <psapi.h>
#include <iostream>
#include <thread>
#include "windows.h"
#include <vector>
#include <string>
#include "Messages.h"

using std::vector;
using std::string;


void test(const Messages &messages) {
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
    messages.sendText("hey");
    Sleep(1000);
    messages.sendKeyTap(KEY_RETURN);

    //    typeText(childWindows, "THIS TEXT IS BEING TYPED ASYNCHRONOUSLY ON A BACKGROUND NOTEPAD WINDOW", hTimerQueue);
    //    Sleep(10000);
}

//bool uniquePred(const HwndTitlePair &l, const HwndTitlePair &r) {
//    return l.first == r.first;
//}

int main() {
    vector<HWND> topWindows = getTopWindows();
    int i = 0;
    for (const auto &hwnd: topWindows) {
        string windowText = getWindowText(hwnd);
        std::cout << i << ": " << windowText << " " << hwnd << std::endl;
        i++;
//        HwndTitleVec subWindowsVec = getChildWindows(p.first);
//        for (const auto &p2: subWindowsVec) {
//            std::cout << "\t" << p2.second << " " << p2.first << std::endl;
//        }
    }
    // todo sort the windows by name
    //    sort(childWindows.begin(), childWindows.end()); // for unique
    //    childWindows.erase(std::unique(childWindows.begin(), childWindows.end(), uniquePred), childWindows.end());

    std::cout << "Please choose a window." << std::endl;
    int decision;
    std::cin >> decision;
    vector<HWND> childWindows = getChildWindows(topWindows[decision]);
    childWindows.push_back(topWindows[decision]);
    Messages messages(childWindows);
    test(messages);
    return 0;
}