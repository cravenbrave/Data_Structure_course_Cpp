#include <iostream>

using std::cout;
using std::endl;

int main(int argc, const char *argv[]) {
  int x = 5, y = 7;
  int a[] = {11, 22, 33, 44, 55};
  int *p = &x;

  cout << "sizeof(int) == " << sizeof(int) << endl;
  cout << "sizeof(int*) == " << sizeof(int*) << endl;
  cout << "x == " << x << "  (at address " << &x << ")" << endl;
  cout << "y == " << y << "  (at address " << &y << ")" << endl;
  cout << "a == " << a << "  (at address " << &a << ")" << endl;
  cout << "p == " << p << "  (at address " << &p << ")" << endl;
  //p's value is &x
  //&p is p's address, differ than &x
  //*p == x
  cout << endl;

  p = a; // same as p = &a[0];
  cout << "Now p == " << p << " == a == " << a << endl;
  cout
      << "*a == " << *a << " && a[0] == " << a[0] << " && "
      << "*p == " << *p << " && p[0] == " << p[0]
      << "  at address " << a << " " << p << endl;
      //a == a's address == p's value
  for (int i = 0; i < 5; ++i) {
    cout
    //*(a + 0) == 11 at a[0]'s address    a[0] == 11 at a[0]'s address *(p + 0) == 11 at a[0]'s address
    //    p[0] = 11 at p's/a[0]'s address

    //*(a + 1) == 22 at a[1]'s address a[1] == 22 at a[1]'s address *(p + 1) == 22 at a[1]'s address
    //p[1] == 22 at a[1]'s address
        << "*(a + " << i << ") == " << *(a + i) << "  at " << a + i << endl
        << "    a[" << i << "] == " << a[i]     << "  at " << &a[i] << endl
        << "*(p + " << i << ") == " << *(p + i) << "  at " << p + i << endl
        << "    p[" << i << "] == " << p[i]     << "  at " << &p[i] << endl;
  }
  cout << endl;

  cout << "You can iterate using indices in an array or with pointers:" << endl;
  int *begin = a, *end = a + 5;
  for (int *p = begin; p != end; ++p) {
    cout
        << "int at address " << p << " is " << *p << " which is "
        << p - begin << " ints from address " << begin << endl;
  }
  return 0;
}