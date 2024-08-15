//
// Created by roi65 on Thu 15/08/2024.
//

#include "windows.h"


vector<HWND> getTopWindows() {
    vector<HWND> topWindows;
    for (HWND hwnd = GetTopWindow(nullptr); hwnd != nullptr; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) {
        if (!IsWindowVisible(hwnd))
            continue;
        string windowText = getWindowText(hwnd);
        if (windowText == "This PC") {
            continue;
        }
        if (windowText == "Tools") {
            continue;
        }
        topWindows.push_back(hwnd);
    }
    return topWindows;
}


vector<HWND> getChildWindows(HWND parent) {
    vector<HWND> childWindows;
    EnumChildWindows(parent, [](HWND hwnd, LPARAM lParam) {
        auto *vec = reinterpret_cast<vector<HWND> *>(lParam);
        vec->push_back(hwnd);
        return TRUE;
    }, reinterpret_cast<LPARAM>(&childWindows));
    for (const auto &hwnd: childWindows) {
        vector<HWND> childSubWindows = getChildWindows(hwnd);
        childWindows.insert(childWindows.end(), childSubWindows.begin(), childSubWindows.end());
    }
    return childWindows;
}

string getWindowText(HWND hwnd) {
    int windowTextLength = GetWindowTextLength(hwnd);
    char *windowText = new char[windowTextLength + 1];
    GetWindowText(hwnd, windowText, windowTextLength + 1);
    string windowTextString(windowText);
    delete[] windowText;
    return windowTextString;
}

vector<string> getWindowTexts(const vector<HWND> &hwnds) {
    vector<string> windowTexts;
    for (const auto &hwnd: hwnds) {
        windowTexts.push_back(getWindowText(hwnd));
    }
    return windowTexts;
}