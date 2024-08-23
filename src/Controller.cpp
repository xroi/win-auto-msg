//
// Created by roi65 on Thu 15/08/2024.
//

#include "Controller.hpp"


Controller::Controller(HWND hwnd) {
    this->hTimerQueue = CreateTimerQueue();
    this->hwnds.push_back(hwnd);
}

Controller::Controller(const vector<HWND> &hwnds) {
    this->hTimerQueue = CreateTimerQueue();
    for (const auto &hwnd: hwnds) {
        this->hwnds.push_back(hwnd);
    }
}

Controller::~Controller() {
    DeleteTimerQueue(hTimerQueue);
}

void Controller::sendKey(VKey key, unsigned long durationMS) const {
    WPARAM wParam = key;
    LPARAM lParam = computeKbdLParam(1, key, 0, 0, 0, 0);
    this->postMessageToAll(WM_KEYDOWN, wParam, lParam);

    int callbackMsg = WM_KEYUP;
    WPARAM callbackWParam = key;
    LPARAM callbackLParam = computeKbdLParam(1, key, 0, 0, 1, 1);
    initTimer(callbackMsg, callbackWParam, callbackLParam, durationMS);
}


void Controller::initTimer(int msg, WPARAM wparam, LPARAM lparam,
                           unsigned long durationMS) const{
    HANDLE hTimer = nullptr;
    auto *callbackParam = new CallbackParam{const_cast<Controller *>(this),
                                            msg,
                                            wparam,
                                            lparam};
    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, timerCallback,
                               callbackParam,
                               durationMS, 0, 0)) {
        DEBUG("CreateTimerQueueTimer failed (%d)");
        return;
    }
    DEBUG("SetWaitableTimer sucess");
}


void CALLBACK Controller::timerCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
    auto *callbackParam = (CallbackParam *) lpParam;
    DEBUG("Timer triggered");

    callbackParam->controller->postMessageToAll(callbackParam->msg, callbackParam->wparam, callbackParam->lparam);
    delete callbackParam;
}


void Controller::sendKeyTap(VKey key) const {
    this->sendKey(key, getTapDurationMS());
}

void Controller::sendText(const string &text) const {
    for (const char &c: text) {
        sendKeyTap((VKey) toupper(c));
        // todo allow symbols, capital letters
    }
}

LPARAM Controller::computeKbdLParam(UINT repeatCount, UINT key, byte extended,
                                    byte contextCode, byte previousState,
                                    byte transitionState) {
    LPARAM lParam = repeatCount;
    UINT scanCode = MapVirtualKey((UINT) key, MAPVK_VK_TO_CHAR);
    lParam += (UINT) (scanCode              * 0x10000);
    lParam += (UINT) (extended              * 0x1000000);
    lParam += (UINT) ((contextCode     * 2) * 0x10000000);
    lParam += (UINT) ((previousState   * 4) * 0x10000000);
    lParam += (UINT) ((transitionState * 8) * 0x10000000);
    return lParam;
}

LPARAM Controller::computeMouseLParam(int xCoord, int yCoord) {
    return (int)((yCoord << 16) | (xCoord & 0xFFFF));
}

WPARAM Controller::computeMouseWParam() {
    return 0;
}


void
Controller::postMessageToAll(UINT msg, WPARAM wParam, LPARAM lParam) const {
    for (const auto &hwnd: hwnds) {
        PostMessage(hwnd, msg, wParam, lParam);
    }
}

void Controller::sendMouse(MType type, unsigned long durationMS, int xCoord,
                           int yCoord) const {
    WPARAM wParam = computeMouseWParam();
    LPARAM lParam = computeMouseLParam(xCoord, yCoord);
    switch (type) {
        case LButton:
            this->postMessageToAll(WM_LBUTTONDOWN, wParam, lParam);
            initTimer(WM_LBUTTONUP, wParam, lParam, durationMS);
            break;
        case RButton:
            this->postMessageToAll(WM_RBUTTONDOWN, wParam, lParam);
            initTimer(WM_RBUTTONUP, wParam, lParam, durationMS);
            break;
        case MButton:
            this->postMessageToAll(WM_MBUTTONDOWN, wParam, lParam);
            initTimer(WM_MBUTTONUP, wParam, lParam, durationMS);
            break;
    }
}

void Controller::sendMouseTap(MType type, int xCoord, int yCoord) const {
    this->sendMouse(type, getTapDurationMS(), xCoord, yCoord);
}



