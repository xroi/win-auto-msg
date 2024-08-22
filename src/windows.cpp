//
// Created by roi65 on Thu 15/08/2024.
//

#include "windows.h"


vector<HWND> getTopWindows() {
    vector<HWND> topWindows;
    for (HWND hwnd = GetTopWindow(nullptr);
         hwnd != nullptr; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) {
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
        childWindows.insert(childWindows.end(),
                            childSubWindows.begin(),
                            childSubWindows.end());
    }
    return childWindows;
}

bool isValidWindow(HWND hwnd){
    if (!IsWindowVisible(hwnd))
        return false;
    string windowText = getWindowText(hwnd);
    if (windowText == "This PC" ||
        windowText == "Tools" ||
        windowText.empty()) {
        return false;
    }
    return true;
}



WindowTree getValidWindowTree(){
    WindowTree windowTree;
    vector<HWND> topWindows = getTopWindows();
    auto removeIfIt = std::remove_if(topWindows.begin(),
                                                topWindows.end(),
                                                [](HWND hwnd)
                                               {return !isValidWindow(hwnd);});
    topWindows.erase(removeIfIt, topWindows.end());
    std::sort(topWindows.begin(), topWindows.end());
    topWindows.erase(std::unique(topWindows.begin(),
                                 topWindows.end()),
                                 topWindows.end());

    for (const auto &hwnd: topWindows) {
        vector<HWND> childWindows = getChildWindows(hwnd);
        auto childRemoveIfIt = std::remove_if(childWindows.begin(),
                                                         childWindows.end(),
                                                         [](HWND hwnd)
                                                {return !isValidWindow(hwnd);});
        childWindows.erase(childRemoveIfIt, childWindows.end());
        std::sort(childWindows.begin(), childWindows.end());
        childWindows.erase(std::unique(childWindows.begin(),
                                       childWindows.end()),
                                       childWindows.end());
        windowTree.childWindows.push_back(childWindows);
    }
    windowTree.topWindows = topWindows;
    return windowTree;
}

string getWindowText(HWND hwnd) {
    int windowTextLength = GetWindowTextLength(hwnd);
    char *windowText = new char[windowTextLength + 1];
    GetWindowText(hwnd, windowText, windowTextLength + 1);
    string windowTextString(windowText);
    delete[] windowText;
    return windowTextString;
}

//vector<string> getWindowTexts(const vector<HWND> &hwnds) {
//    vector<string> windowTexts;
//    for (const auto &hwnd: hwnds) {
//        windowTexts.push_back(getWindowText(hwnd));
//    }
//    return windowTexts;
//}



vector<HWND> chooseWindows() {
    printf("================================\n");
    printf("idx  : hWnd     : Window Text\n");
    printf("================================\n");
    WindowTree windowTree = getValidWindowTree();
    for (int i = 0; i < windowTree.topWindows.size(); i++){
        HWND hwnd         = windowTree.topWindows[i];
        string windowText = getWindowText(hwnd);
        printf("%-5d: %-8d : %-30s\n", i, hwnd, windowText.c_str());
        for (int j = 0; i < windowTree.childWindows[i].size(); j++){
            HWND childHwnd         = windowTree.childWindows[i][j];
            string childWindowText = getWindowText(childHwnd);
            printf("\t%d.%d: %s %d\n", i, j, windowText.c_str(), childHwnd);
        }
    }
    std::cout << "Please choose a window." << std::endl;
    int decision;
    std::cin >> decision;
    windowTree.childWindows[decision].push_back(windowTree.topWindows[decision]);
    return windowTree.childWindows[decision];
}
