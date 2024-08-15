//
// Created by roi65 on Thu 15/08/2024.
//

#include "Messages.h"


Messages::Messages(HWND hwnd) {
    this->hTimerQueue = CreateTimerQueue();
    this->hwnds.push_back(hwnd);
}

Messages::Messages(const vector<HWND> &hwnds) {
    this->hTimerQueue = CreateTimerQueue();
    for (const auto &hwnd: hwnds) {
        this->hwnds.push_back(hwnd);
    }
}

Messages::~Messages() {
    DeleteTimerQueue(hTimerQueue);
}

void Messages::sendKey(VKeys key, unsigned long durationMS) const {
    WPARAM wParam = key;
    LPARAM lParam = computeLParam(1, key, 0, 0, 0, 0);
    this->postMessageToAll(WM_KEYDOWN, wParam, lParam);
    HANDLE hTimer = nullptr;
    auto *callbackParam = new CallbackParam{const_cast<Messages *>(this), key};
    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, endKey, callbackParam, durationMS, 0, 0)) {
        DEBUG("CreateTimerQueueTimer failed (%d)");
        return;
    }
    DEBUG("SetWaitableTimer sucess");
}

void Messages::endKey(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
    auto *callbackParam = (CallbackParam *) lpParam;
    DEBUG("Timer triggered");
    WPARAM wParam = callbackParam->key;
    LPARAM lParam = computeLParam(1, callbackParam->key, 0, 0, 1, 1);
    callbackParam->messages->postMessageToAll(WM_KEYUP, wParam, lParam);
    delete callbackParam;
}


void Messages::sendKeyTap(VKeys key) const {
    this->sendKey(key, getTapDurationMS());
}

void Messages::sendText(const string &text) const {
    for (const char &c: text) {
        sendKeyTap((VKeys) c);
        // todo handle non capital letters etc
    }
}


LPARAM Messages::computeLParam(UINT repeatCount, UINT key, byte extended, byte contextCode, byte previousState,
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

void Messages::postMessageToAll(UINT msg, WPARAM wParam, LPARAM lParam) const {
    for (const auto &hwnd: hwnds) {
        PostMessage(hwnd, msg, wParam, lParam);
    }
}