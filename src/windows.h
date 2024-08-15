//
// Created by roi65 on Thu 15/08/2024.
//

#ifndef AUTO_WIN_MSG_PROCESSES_H
#define AUTO_WIN_MSG_PROCESSES_H

#include "VKeys.h"
#include <windows.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

/*
 * Wrappers for win32 windows api code
 */

vector<HWND> getTopWindows();

vector<HWND> getChildWindows(HWND parent);

string getWindowText(HWND hwnd);

vector<string> getWindowTexts(const vector<HWND> &hwnds);

#endif //AUTO_WIN_MSG_PROCESSES_H
