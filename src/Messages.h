//
// Created by roi65 on Thu 15/08/2024.
//

#ifndef AUTO_WIN_MSG_MESSAGES_C_H
#define AUTO_WIN_MSG_MESSAGES_C_H

#ifdef NDEBUG
#define DEBUG(x)
#else
#define DEBUG(x) do { std::cerr << x << std::endl; } while (0)
#endif

#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "VKeys.h"

using std::string;
using std::vector;

class Messages {
public:
    explicit Messages(HWND hwnd);

    explicit Messages(const vector<HWND> &hwnds);

    ~Messages();

    void sendKey(VKeys key, unsigned long durationMS) const;

    void sendKeyTap(VKeys key) const;

    void sendText(const string &text) const;

    static int getTapDurationMS() { return 100; }

private:
    HANDLE hTimerQueue;
    vector<HWND> hwnds;

    struct CallbackParam {
        Messages *messages;
        VKeys key;
    };

    void postMessageToAll(UINT msg, WPARAM wParam, LPARAM lParam) const;

    static LPARAM computeLParam(UINT repeatCount, UINT key, byte extended, byte contextCode, byte previousState,
                                byte transitionState);

    static void CALLBACK endKey(PVOID lpParam, BOOLEAN TimerOrWaitFired);
};


#endif //AUTO_WIN_MSG_MESSAGES_C_H
