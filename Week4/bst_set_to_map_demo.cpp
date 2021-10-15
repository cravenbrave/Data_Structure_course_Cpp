#include <iostream>
#include <string>

#include "bst_map.h"

using namespace std;

int main()
{
    BinarySearchTree<char, string> bst;
    // bst[11] = "eleven";
    // bst[55] = "fifty five";
    // bst[99] = "ninety nine";
    // // BinarySearchTree<int, string>::Iterator it(bst.root);

    // // it.print_stack_keys();
    // cout << "bst before using operator[]:" << endl;
    // bst.print();
    // cout << endl;

    // for (int x : {0, 11, 33, 55, 88, 99, 1000})
    // {
    //     cout << "bst[" << x << "] == " << bst[x] << endl;
    // }
    // cout << endl;

    // cout << "bst after using operator[]:" << endl;
    // bst.print();

    bst.insert('r', "Root");
    bst.insert('c', "Coconut");
    bst.insert('a', "Apple");
    bst['b'] = "Bursley";
    bst['d'] = "Dexter";
    bst['e'] = "Element";
    bst.print();
    cout << endl;

    for (char c : {'z', 'm', 'c', 'r'}){
        cout << "Tree, after removing " << c << ": " << endl;
        cout << "Erased " << bst.erase(c) << " elements" <<endl;
        bst.print();
        cout << endl;
    }

    // cout << bst.largest_node()->value << endl;
    return 0;
}