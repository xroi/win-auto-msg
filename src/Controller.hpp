//
// Created by roi65 on Thu 15/08/2024.
//

#ifndef AUTO_WIN_MSG_CONTROLLER_HPP
#define AUTO_WIN_MSG_CONTROLLER_HPP

#ifdef NDEBUG
#define DEBUG(x)
#else
#define DEBUG(x) do { std::cerr << x << std::endl; } while (0)
#endif

#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include "VKey.hpp"
#include "MType.hpp"

using std::string;
using std::vector;

class Controller {
public:
    explicit Controller(HWND hwnd);

    explicit Controller(const vector<HWND> &hwnds);

    ~Controller();

    void sendKey(VKey key, unsigned long durationMS) const;

    void sendKeyTap(VKey key) const;

    void sendText(const string &text) const;

    void sendMouse(MType type, unsigned long durationMS, int xCoord, int yCoord) const;

    void sendMouseTap(MType type, int xCoord, int yCoord) const;

    static int getTapDurationMS() { return 100; }



private:
    HANDLE hTimerQueue;
    vector<HWND> hwnds;

    struct CallbackParam {
        Controller *controller;
        int msg;
        WPARAM wparam;
        LPARAM lparam;
    };

    void postMessageToAll(UINT msg, WPARAM wParam, LPARAM lParam) const;

    static LPARAM computeKbdLParam(UINT repeatCount, UINT key, byte extended,
                                   byte contextCode, byte previousState,
                                   byte transitionState);

    static LPARAM computeMouseLParam(int xCoord, int yCoord);

    static WPARAM computeMouseWParam();

    // Sends the message with the parameters after durationMS time.
    void initTimer(int msg, WPARAM wparam, LPARAM lparam, unsigned long durationMS) const;

    static void CALLBACK timerCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired);

};


#endif //AUTO_WIN_MSG_CONTROLLER_HPP
