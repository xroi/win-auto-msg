#include <windows.h>
#include <thread>
#include <vector>
#include <string>

#include "Controller.hpp"
#include "windows.hpp"
#include "MouseLocator.hpp"

void printMenu();

using std::vector;
using std::string;


void test(const Controller &controller) {

//    while (true){
//        controller.sendKeyTap(KEY_D);
//        controller.sendMouseTap(LButton, 125, 218);
//        Sleep(30000);
//    }

//    controller.sendKeyTap(KEY_A);
//    Sleep(1000);
//    controller.sendKeyTap(KEY_D);
//    Sleep(1000);
//    controller.sendKeyTap(KEY_A);
//    Sleep(1000);
//    controller.sendKeyTap(KEY_D);
//    controller.sendKeyTap(KEY_W);
//    Sleep(1000);
//    controller.sendKeyTap(KEY_RETURN);
//    Sleep(1000);
//    controller.sendText("HEY");
//    Sleep(1000);
//    controller.sendText("hey!");
//    Sleep(1000);
//    controller.sendKeyTap(KEY_RETURN);

//    controller.sendText("wwWwwwwwwwwwwwwWwwwwwwwWwwwwwwww");
    controller.sendText("This text is being typed asynchronously on a non-focused background window. Cool");
    Sleep(1000);
}

void automation(){
    vector<HWND> windows = chooseWindows();
    Controller controller(windows);
    test(controller);
}

void mouseLocatorUtil(){
    vector<HWND> windows = chooseWindows();
    trackMouse(windows.back());
}

int main() {
    while (true){
        printMenu();
        int decision;
        std::cin >> decision;
        switch (decision) {
            case 1:
                automation();
                break;
            case 2:
                mouseLocatorUtil();
                break;
            case 3:
                printf("Not implemented :(\n");
                break;
            case 4:
            default:
                exit(0);
        }
    }
}

void printMenu() {
    printf("=========================\n");
    printf("Please choose a function:\n");
    printf("=========================\n");
    printf("1. Run Automation\n");
    printf("2. Mouse Locator Utility\n");
    printf("3. Recording mode\n");
    printf("4. Exit\n");
}
