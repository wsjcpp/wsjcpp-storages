
#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include <wsjcpp_storages.h>

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    if (!WSJCppCore::dirExists(".wsjcpp")) {
        WSJCppCore::makeDir(".wsjcpp");
    }
    std::string appLogPath = ".wsjcpp/logs";
    if (!WSJCppCore::dirExists(appLogPath)) {
        WSJCppCore::makeDir(appLogPath);
    }
    WSJCppLog::setPrefixLogFile("wsjcpp");
    WSJCppLog::setLogDirectory(".wsjcpp/logs");

    std::vector<std::string> vArgs;

    for (int i = 0; i < argc; i++) {
        vArgs.push_back(std::string(argv[i]));
    }

    /*if (vArgs.size() != 3) {
        std::cout << "Usage: " << vArgs[0] << " <string1> <string2>" << std::endl;
        return -1;
    }

    std::string s1 = vArgs[1];
    std::string s2 = vArgs[2];
    int nDistance = WSJCppLevenshtein::distance(s1,s2);
    std::cout << "" << nDistance << std::endl;*/
    return 0;
}