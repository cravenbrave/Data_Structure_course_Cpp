#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "compromise_search.h"

using namespace std;

int main() {

    const int FUNC_CALL_COUNT = 1000;
    const double RATIO_MID = 0.2;
    const double RATIO_HIGH = 0.8;

    // print the header
    printf(
        //s: string  int:d f:floating point,
        "%15s %30s %30s %30s %30s %30s\n", 
        "Array length", 
        "std::binary_search",
        "compromise_search low",
        "compromise_search mid",
        "compromise_search high",
        "std::find"
    );

    // profile time vs array size
    for (int i = 1; i <= 100; ++i) {
        int size = i * 100;
        vector<int> array(size, 0);
        for (int j = 0; j < size; ++j) {
            array[j] = j;
        }

        // profile std::binary_search
        clock_t start_time = clock();
        for (int j = 0; j < FUNC_CALL_COUNT; ++j) {
            int target = rand() % size; // target in [0, size - 1]
            auto index = binary_search(array.begin(), array.end(), target);
        }
        clock_t stop_time = clock();
        double time1 = static_cast<double>(stop_time - start_time) / CLOCKS_PER_SEC;

        // profile compromise_search with low ratio for small_window
        start_time = clock();
        for (int j = 0; j < FUNC_CALL_COUNT; ++j) {
            int target = rand() % size; // target in [0, size - 1]
            int small_window = 10;
            auto index = compromise_search(array.begin(), array.end(), target, small_window);
        }
        stop_time = clock();
        double time2 = static_cast<double>(stop_time - start_time) / CLOCKS_PER_SEC;

        // profile compromise_search with medium ratio for small_window
        start_time = clock();
        for (int j = 0; j < FUNC_CALL_COUNT; ++j) {
            int target = rand() % size; // target in [0, size - 1]
            int small_window = static_cast<int>(size * RATIO_MID);
            auto index = compromise_search(array.begin(), array.end(), target, small_window);
        }
        stop_time = clock();
        double time3 = static_cast<double>(stop_time - start_time) / CLOCKS_PER_SEC;

        // profile compromise_search with high ratio for small_window
        start_time = clock();
        for (int j = 0; j < FUNC_CALL_COUNT; ++j) {
            int target = rand() % size; // target in [0, size - 1]
            int small_window = static_cast<int>(size * RATIO_HIGH);
            auto index = compromise_search(array.begin(), array.end(), target, small_window);
        }
        stop_time = clock();
        double time4 = static_cast<double>(stop_time - start_time) / CLOCKS_PER_SEC;

        // profile linear search with std::find
        start_time = clock();
        for (int j = 0; j < FUNC_CALL_COUNT; ++j) {
            int target = rand() % size; // target in [0, size - 1]
            int small_window = static_cast<int>(size * RATIO_HIGH);
            auto index = find(array.begin(), array.end(), target);
        }
        stop_time = clock();
        double time5 = static_cast<double>(stop_time - start_time) / CLOCKS_PER_SEC;

        // Output in tabular format
        printf(
            //xiaoshudianhou
            "%15d %30.9f %30.9f %30.9f %30.9f %30.9f\n",
            size,
            time1,
            time2,
            time3,
            time4,
            time5
        );
    }
    return 0;
}