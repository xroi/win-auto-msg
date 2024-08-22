//
// Created by roi65 on Thu 15/08/2024.
//

#ifndef AUTO_WIN_MSG_PROCESSES_H
#define AUTO_WIN_MSG_PROCESSES_H

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "VKey.h"

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

#endif //AUTO_WIN_MSG_PROCESSES_H
