#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;

// O(length) time overall for this insert function
int *insert(int *array, int length, int index, int value) {

    int* newArray = NULL;                      // O(1) time

    // input array is empty, return a new array with length 1 and the target value
    if (length == 0) {                         // O(1) time overall for if
        newArray = new int[1];                 // O(1) time
        newArray[0] = value;                   // O(1) time
        return newArray;                       // O(1) time
    }

    newArray = new int[length + 1];            // O(1) time

    // copy array[0, index) to newArray[0, index)
    for (int i = 0; i < index; ++i) {          // O(index) time overall
        newArray[i] = array[i];                // O(1) time
    }

    newArray[index] = value;                   // O(1) time

    // copy array[index, length) to newArray[index + 1, length + 1)
    for (int i = index; i < length; ++i) {     // O(length - index) time overall
        newArray[i + 1] = array[i];            // O(1) time
    }

    delete [] array; // free the memory of the old array, O(1) time
    return newArray;                           // O(1) time
}

int main() {

    const int INSERTS_PER_READING = 1000;

    // start with an empty array
    int* array = NULL;
    int length = 0;

    // print the header
    printf("%15s %20s\n", "Array length", "Seconds per insert");

    // take 60 readings
    for (int i = 0; i < 60; ++i) {
        clock_t startTime = clock();

        // Each reading will be taken after INSERTS_PER_READING inserts
        for (int j = 0; j < INSERTS_PER_READING; ++j) {
            int index = rand() % (length + 1); // random index in [0, length]
            int value = rand(); // random integer value
            array = insert(array, length, index, value);
            length++;
        }

        clock_t stopTime = clock();
        double timePerInsert = static_cast<double>(stopTime - startTime) 
            / CLOCKS_PER_SEC / INSERTS_PER_READING;

        // Output reading in tabular format
        printf("%15d %20.8f\n", (i + 1) * INSERTS_PER_READING, timePerInsert);
    }

    // free the old array
    delete [] array;
    return 0;
}