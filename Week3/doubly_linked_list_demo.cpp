#include <iostream>
#include <string>

#include "doubly_linked_list.h"

using std::cout;
using std::endl;
using std::string;

int main()
{
    LinkedList<string> words;
    words.push_back("apple");
    words.push_back("banana");
    words.push_back("cherry");

    LinkedList<string>::Iterator it = words.begin();

    ++it;
    ++it;
    ++it;
    //   words.pop_front();
    words.insert(it, "orange");

    for (const string &word : words)
    {
        cout << word << endl;
    }
    return 0;
}