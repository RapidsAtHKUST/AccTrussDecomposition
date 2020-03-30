//
// Created by yche on 7/14/19.
//
#include <vector>
#include "util/log/log.h"

int get_log_size(int x) {
    int cnt = 0;
    for (; x > 0; cnt++) {
        x >>= 1;
    }
    return cnt;
}

int get_part_size(int i) {
    return i == 0 ? 0 : 1 << (get_log_size(i) - 1);
}

int get_radix(int i) {
    return get_part_size(i) - 1;
}

using namespace std;

int main() {
    log_info("sizeof(vector<int>): %zu", sizeof(vector<int>));
    log_info("alignof(vector<int>): %zu", alignof(vector<int>));
    for (auto i = 0; i < 16; i++) {
        auto log_size = get_log_size(i);
        log_info("log_size: %d, part: %d, org-size: %d, raidx: %x", log_size, i == 0 ? 0 : 1 << (log_size - 1), i,
                 get_radix(i) & 0xff);
    }
}