//
// Created by roi65 on Fri 23/08/2024.
//


#include "MouseLocator.hpp"

POINT getMousePosRelativeToWindow(HWND hwnd) {
    POINT screenPos, clientPos;
    RECT windowRect, clientRect;
    GetCursorPos(&screenPos);
    GetWindowRect(hwnd, &windowRect);
    GetClientRect(hwnd, &clientRect);
    int borderWidth = (windowRect.right - windowRect.left - clientRect.right) / 2;
    int titlebarHeight = (windowRect.bottom - windowRect.top - clientRect.bottom) - borderWidth;
    // Calculate relative position
    clientPos.x = screenPos.x - windowRect.left - borderWidth;
    clientPos.y = screenPos.y - windowRect.top - titlebarHeight;
    return clientPos;
}

void trackMouseLoop(std::atomic<bool>& running, HWND hwnd){
    while (running){
        POINT pos = getMousePosRelativeToWindow(hwnd);
        printf("Current Position: (%ld,%ld)\n", pos.x, pos.y);
        Sleep(500); // MS
    }
}

void trackMouse(HWND hwnd) {
    std::atomic<bool> running(true);
    std::thread trackerThread(trackMouseLoop, std::ref(running), hwnd);
    system("pause"); // Wait for any input
    running = false;
    trackerThread.join();
}
