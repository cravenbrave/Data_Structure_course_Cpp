#include <iostream>
#include <string>

using namespace std;

int main()
{
    int count = 0;
    string a[200] = {"a"};
    string b[100] = {"a"};

    for (string i : a)
    {
        for (string j : b)
        {
            // if (j.compare(i) != 0)
            // {
            // }
            count ++;
        }
    }

    cout << count << endl;
    return 0;
}