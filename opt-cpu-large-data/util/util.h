#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <cstring>
#include <cstdlib>
#include <cstdint>

#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include <memory>

#include "util/log/log.h"

using namespace std;

template<class T>
std::string FormatWithCommas(T value) {
    string numWithCommas = to_string(value);
    int insertPosition = numWithCommas.length() - 3;
    while (insertPosition > 0) {
        numWithCommas.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    return numWithCommas;
}

inline void reset(std::stringstream &stream) {
    const static std::stringstream initial;

    stream.str(std::string());
    stream.clear();
    stream.copyfmt(initial);
}