//
// Created by roi65 on Thu 15/08/2024.
//

#ifndef AUTO_WIN_MSG_WINDOWS_HPP
#define AUTO_WIN_MSG_WINDOWS_HPP

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "VKey.hpp"

using std::string;
using std::vector;

struct WindowTree{
    vector<HWND> topWindows;
    vector<vector<HWND>> childWindows;
};


/*
 * Wrappers for win32 windows api code
 */

vector<HWND> getTopWindows();

vector<HWND> getChildWindows(HWND parent);

string getWindowText(HWND hwnd);

WindowTree getValidWindowTree();

vector<HWND> chooseWindows();

#endif //AUTO_WIN_MSG_WINDOWS_HPP
