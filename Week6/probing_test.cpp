#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <utility>
#include "hash_p.h"
using namespace std;

int main()
{
    ProbingHashTable<string, int> table;
    // for (int i = 0; i < 16; i++) {
    //     table.insert(i, i*i);
    //     // cout << table.insert(i, i*i) << endl;
    //     // cout << table.size() << endl;
    // }
    
    for (int i = 0; i < 20; ++i)
    {
        string k = to_string(i);
        // cout << "table contains (" << k << "): " << table.contains(k) << endl;
        table.insert(k, i * i);
        // cout << "table contains (" << k << "): " << table.contains(k) << endl;
    }

    for (int i = 15; i < 25; i++) {
        string k = to_string(i);
        cout << "table contains (" << k << "): " << table.get(k) << endl;
    }
    table.print();
    return 0;
}