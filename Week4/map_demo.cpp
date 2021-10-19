#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <random>

using namespace std;

default_random_engine DRE;
//get a random elements from the vector
const string &getRandomWord(const std::vector<std::string> &words, default_random_engine &dre = DRE)
{
    // std::default_random_engine dre;
    std::uniform_int_distribution<int> uniform_dist(0, words.size() - 1);
    return words[uniform_dist(dre)];
}
int main()
{
    map<string, vector<string> > nextWords;
    ifstream f("words_independence.txt");

    //lastW is used to store all words in f file after lastW
    //eg. lastW = wendy, nextWords[wendy] will store all words in form of vector from f after wendy
    for (string lastW, w; f >> w; lastW = w)
    {
        // words.insert(w);
        //in this loop, lastW will be empty
        // cout << "nextW: " << lastW << endl;
        // cout << "w: " << w << endl;
        nextWords[lastW].push_back(w);
    }
    // cout << words.size() << endl;
    // //give you the range btw b and c
    // auto start = words.lower_bound("b");
    // auto end = words.lower_bound("c");

    //cout all words after to
    for (const auto &w : nextWords["to"])
    {
        // cout << "to " << w << endl;
    }

    string input = "to";
    for (int i = 0; i < 100; i++){
        cout << input << " ";
        //change lines every 10 words
        if (i %10 == 0 ){
            cout << endl;
        }
        input = getRandomWord(nextWords["to"]);
    }

    cout << endl;

    return 0;
}