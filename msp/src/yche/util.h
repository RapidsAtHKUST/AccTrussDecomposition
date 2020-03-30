#pragma once

#include <string>

#include <iomanip>
#include <locale>
#include <sstream>

using namespace std;

template<class T>
std::string FormatWithCommas(T value) {
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << value;
    return ss.str();
}

