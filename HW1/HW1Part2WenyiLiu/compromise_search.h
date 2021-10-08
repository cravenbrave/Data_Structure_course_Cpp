// Compromise Search is a compromise between Binary Search and Linear Search:
//   We use Binary Search until we get to small_size elements, then we switch to Linear Search.
//   Binary Search between low and high until the gap between low and high is <= small_size,
//   then use std::find on the range (from low to high).
// For example,
// vector<string> words = {"aaa", "bbb", "ccc", "ddd", "eee"};
// cout << *compromise_search(words.begin(), words.end(), "bbb", 3) << endl;
// will print "bbb\n".
// compromise_search will
// - calculate the middle
// - see that "bbb" < "ccc" (and update the upper bound)
// - see that the remaining range (from "aaa" to "ccc" exclusive)
//   has <= small_size (3) elements
// - use std::find to search through the remaining range
//   (from "aaa" to "ccc" exclusive)
//
// RandomAccessIt is a random-access iterator, like vector<string>::begin().
// low is inclusive and high is exclusive.
template<class RandomAccessIt, class T>
RandomAccessIt compromise_search(
    RandomAccessIt low, RandomAccessIt high, const T& value, int small_size) {
  
  RandomAccessIt end = high; // if value not found, return end at the end
  while (low < high) {
    RandomAccessIt mid = low + (high - low) / 2;
    if (*mid == value) {
      return mid;
    }
    if (*mid < value) {
      low = mid + 1;
    } else {
      high = mid;
    }
    // switch to linear search
    if (high - low <= small_size) {
      break;
    }
  }

  RandomAccessIt ans = std::find(low, high, value);
  return ans == high ? end : ans;
}