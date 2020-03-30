//
// Created by yche on 5/22/19.
//

#include <string>
#include <iostream>
#include <tbb/concurrent_hash_map.h>

using namespace std;

int main() {
    tbb::concurrent_hash_map<std::string, int> nameMap;
    nameMap.emplace("", 1);

    string cmd("abc");
    cout << cmd.find_last_of('/', -1) << string::npos << endl;

    exit(-1);

    cout << sizeof(long) << endl;
}
