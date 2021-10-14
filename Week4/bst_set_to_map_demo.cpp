#include <iostream>
#include <string>

#include "bst_map.h"

using namespace std;

int main()
{
    BinarySearchTree<int, string> bst;
    bst[11] = "eleven";
    bst[55] = "fifty five";
    bst[99] = "ninety nine";
    BinarySearchTree<int, string>::Iterator it(bst.root);
    cout << "print iterator: " << endl;
    it.print_stack_keys();
    cout << "print iterator after: " << endl;

    // it.print_stack_keys();
    cout << "bst before using operator[]:" << endl;
    bst.print();
    cout << endl;

    for (int x : {0, 11, 33, 55, 88, 99, 1000})
    {
        cout << "bst[" << x << "] == " << bst[x] << endl;
    }
    cout << endl;

    cout << "bst after using operator[]:" << endl;
    bst.print();
    cout << "+++++++++++" << endl;
    it.print_stack_keys();
    cout << (*it).second << endl;
    it.print_stack_keys();
    return 0;
}