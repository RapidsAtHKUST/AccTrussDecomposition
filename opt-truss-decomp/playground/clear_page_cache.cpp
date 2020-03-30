//
// Created by yche on 9/6/19.
//

#include <cstdlib>

#include <iostream>

using namespace std;

int main() {
    size_t size = 60L * 1024L * 1024L * 1024L;
    auto arr = (int *) malloc(sizeof(int) * size);
    long sum = 0;
#pragma omp parallel
    {
#pragma omp for
        for (size_t i = 0; i < size; i += 1 ) {
            arr[i] = i;
        }
#pragma omp for reduction(+:sum)
        for (size_t i = 0; i < size; i++) {
            sum += arr[i];
        }
    }
    cout << sum << endl;
    free(arr);
}
