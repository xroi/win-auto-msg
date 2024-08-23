#include <windows.h>
#include <thread>
#include <vector>
#include <string>

#include "Controller.hpp"
#include "windows.hpp"

using std::vector;
using std::string;


void test(const Controller &controller) {
    controller.sendKeyTap(KEY_A);
    Sleep(1000);
    controller.sendKeyTap(KEY_D);
    Sleep(1000);
    controller.sendKeyTap(KEY_A);
    Sleep(1000);
    controller.sendKeyTap(KEY_D);
    controller.sendKeyTap(KEY_W);
    Sleep(1000);
    controller.sendKeyTap(KEY_RETURN);
    Sleep(1000);
    controller.sendText("HEY");
    Sleep(1000);
    controller.sendText("hey!");
    Sleep(1000);
    controller.sendKeyTap(KEY_RETURN);

    //    typeText(childWindows, "THIS TEXT IS BEING TYPED ASYNCHRONOUSLY ON A BACKGROUND NOTEPAD WINDOW", hTimerQueue);
    //    Sleep(10000);
}



int main() {
    vector<HWND> windows = chooseWindows();
    Controller controller(windows);
    test(controller);
    return 0;
}