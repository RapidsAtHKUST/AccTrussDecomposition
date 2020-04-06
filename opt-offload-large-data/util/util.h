#pragma once

#include <string>

#include <iomanip>
#include <locale>
#include <sstream>

#include "log/log.h"

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

inline void SetThreadSelfAffinity(int core_id) {
#ifdef NOT_ENOUGH
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    assert(core_id >= 0 && core_id < num_cores);
    if (core_id == 0) {
        printf("affinity relevant logical cores: %ld\n", num_cores);
    }
    core_id = core_id % num_cores;
#endif
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    int ret = pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
    if (ret != 0) {
        log_error("Set affinity error: %d, %s", ret, strerror(errno));
    }
}
