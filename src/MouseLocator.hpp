//
// Created by roi65 on Fri 23/08/2024.
//

#ifndef AUTO_WIN_MSG_MOUSELOCATOR_HPP
#define AUTO_WIN_MSG_MOUSELOCATOR_HPP

#include <windows.h>
#include <thread>
#include <iostream>

POINT getMousePosRelativeToWindow(HWND hwnd);

void trackMouse(HWND hwnd);

#endif //AUTO_WIN_MSG_MOUSELOCATOR_HPP
