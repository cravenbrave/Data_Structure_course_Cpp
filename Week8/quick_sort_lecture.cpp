#include <iostream>
#include <vector>
#include <random>
#include <utility>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::string;
using std::swap;
using std::uniform_int_distribution;
using std::vector;

default_random_engine DRE;
template <typename RandomAccessIt>
RandomAccessIt partition(RandomAccessIt begin, RandomAccessIt end) {
  // Base case: end - begin <= 1
  if (end - begin <= 1) {
    return begin;
  }
  // Randomly pick a pivot
  uniform_int_distribution<int> uniform_dist(0, end - begin - 1);
  int pivot_index = uniform_dist(DRE);
  // Swap the pivot so it's at end - 1.
  RandomAccessIt pivot = end - 1;
  swap(*(begin + pivot_index), *pivot);
  // Partition using the pivot
  RandomAccessIt left = begin, right = pivot - 1;
  while (left <= right) {
    if (*left < *pivot) {
      ++left;
    } else {
      swap(*left, *right);
      --right;
    }
  }
  // Put the pivot in the middle and return an iterator to where the pivot is
  swap(*left, *pivot);
  return left;
}

template <typename RandomAccessIt>
void quick_sort(RandomAccessIt begin, RandomAccessIt end) {
  // Base case: end - begin <= 1
  if (end - begin <= 1) {
    return;
  }
  RandomAccessIt pivot = partition(begin, end);
  // Recurse
  quick_sort(begin, pivot);
  quick_sort(pivot + 1, end);
}


int main()
{
    vector<string> words;
    words.push_back("cherry");
    words.push_back("durian");
    words.push_back("apple");
    words.push_back("egg plant");
    words.push_back("banana");
    words.push_back("ea");

    quick_sort(words.begin(), words.end());
    for (const string &w : words)
    {
        cout << w << endl;
    }
    cout << endl;
    return 0;
}