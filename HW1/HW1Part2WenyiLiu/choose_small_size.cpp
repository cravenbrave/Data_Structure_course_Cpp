#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "compromise_search.h"

using namespace std;

int main() {

    const int FUNC_CALL_COUNT = 1000;
    const int ARRAY_SIZE = 1000;
    vector<int> array(ARRAY_SIZE, 0);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i;
    }

    // print the header
    printf(
        "%15s %30s %30s\n", 
        "small_size", 
        "std::binary_search",
        "compromise_search"
    );

    // profile time vs small_size
    for (int small_size = 0; small_size <= 100; ++small_size) {
        
        // profile std::binary_search
        clock_t start_time = clock();
        for (int i = 0; i < FUNC_CALL_COUNT; ++i) {
            int target = rand() % ARRAY_SIZE; // target in [0, size - 1]
            auto index = binary_search(array.begin(), array.end(), target);
        }
        clock_t stop_time = clock();
        double time1 = static_cast<double>(stop_time - start_time) / CLOCKS_PER_SEC;

        // profile compromise_search
        start_time = clock();
        for (int i = 0; i < FUNC_CALL_COUNT; ++i) {
            int target = rand() % ARRAY_SIZE; // target in [0, size - 1]
            auto index = compromise_search(array.begin(), array.end(), target, small_size);
        }
        stop_time = clock();
        double time2 = static_cast<double>(stop_time - start_time) / CLOCKS_PER_SEC;

        // Output in tabular format
        printf(
            "%15d %30.9f %30.9f\n",
            small_size,
            time1,
            time2
        );
    }
    return 0;
}