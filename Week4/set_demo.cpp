#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main(){
    set<string> words;
    ifstream f("words_independence.txt");

    for (string w; f >> w; ){
        words.insert(w);
    }
    cout << words.size() << endl;
    //give you the range btw b and c
    auto start = words.lower_bound("b");
    auto end = words.lower_bound("c");

    for (auto it = start; it != end; ++it){
        cout << *it << endl;
    }
    return 0;
}