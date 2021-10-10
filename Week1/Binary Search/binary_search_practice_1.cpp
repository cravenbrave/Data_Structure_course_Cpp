#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

vector<string> read_lines(const string &filepath, const long max_lines = -1)
{
    ifstream f(filepath);
    vector<string> lines;
    for (string line; getline(f, line);)
    {
        lines.push_back(line);
        if (max_lines > 0 && lines.size() >= max_lines)
        {
            break;
        }
    }
    return lines;
}

bool isInList(const vector<string> &words, const string &word)
{
    int position = words.size() / 2;
    int i = 0;
    while (i < word.size())
    {
        if (words[position] == word)
        {
            return true;
        }
        else
        {
            if (word > words[position])
            {
                position = (position + words.size()) / 2;
            }
            else
            {
                position = position / 2;
            }
        }
        i++;
    }
    return false;
}

bool bsSearch(const vector<string> &words, const string &word, int low, int high)
{
    if (low == high)
    {
        return false;
    }
    const int middle = low + (high - low) / 2;
    const string &mid_word = words[middle];
    if (word == mid_word)
    {
        return true;
    }
    else if (word > mid_word)
    {
        low = middle + 1;
    }
    else
    {
        high = middle;
    }
    return bsSearch(words, word, low, high);
}

bool bsSearch(const vector<string> &words, const string &word)
{
    return bsSearch(words, word, 0, words.size());
}

double timeUsageMy(const vector<string> &words, const string &word)
{
    auto start_time = std::chrono::steady_clock::now();
    isInList(words, word);
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    return elapsed_seconds.count();
}

double timeUsageT(const vector<string> &words, const string &word)
{
    auto start_time = std::chrono::steady_clock::now();
    bsSearch(words, word);
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;
    return elapsed_seconds.count();
}

int main(int argc, const char *argv[])
{
    const char *words_filename = argc > 1 ? argv[1] : "words.txt";
    vector<string> words = read_lines(words_filename, 10);

    cout << timeUsageMy(words, "engrossed") << endl;
    cout << timeUsageT(words, "engrossed") << endl;
    return 0;
}