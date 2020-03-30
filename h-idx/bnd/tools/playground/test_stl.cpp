//
// Created by yche on 4/26/19.
//

#include <vector>
#include <numeric>
#include <iostream>

#include "util/serialization/pretty_print.h"

using namespace std;

int main() {
    vector<int> test(10);
    iota(begin(test), end(test), 0);
    cout << test << endl;
}
