#include <iostream>
#include <string>

using std::cout;
using std::endl;

template<typename T>
T my_min(const T& x, const T& y) {
  return (x < y) ? x : y;
}

// When you see templates, it's common to use `T` as the typename but you can
// use basically whatever name you want, like you can with variables or classes.
template<typename someTYPEnaaaaame>
someTYPEnaaaaame my_max(const someTYPEnaaaaame& x, const someTYPEnaaaaame& y) {
  return (x > y) ? x : y;
}

int main(int argc, const char *argv[]) {
  std::string apples = "apples", oranges = "oranges";
  cout << my_min(2, 3) << endl;
  cout << my_min(5, 4) << endl;
  cout << my_min(2.2, 3.3) << endl;
  cout << my_min(5.5, 4.4) << endl;
  cout << my_min(apples, oranges) << endl;
  cout << my_max(oranges, apples) << endl;
  return 0;
}