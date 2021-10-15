#include <iostream>
#include <string>
#include <random>

#include "bag.h"

using namespace std;

int main()
{
    cs2c::Bag<int> bag;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> uniform_dist(1, 8);
    for (int i = 0; i < 14; i++)
    {
        bag.insert(uniform_dist(dre));
    }
    
    cout << "Size: " << bag.size() << endl;
    bag.print();
    cout << "_________" << endl;
    cout << bag.remove(2) << endl;
    // cout << bag.remove(6) << endl;
    cout << "Contains 0? "<<bag.contains(0) << endl;
    cout << "Size: " << bag.size() << endl;
    bag.print();
    return 0;
}