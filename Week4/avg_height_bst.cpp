#include <iostream>
#include <cmath>
#include <map>

using namespace std;

double avg_bst_height(int n, map<int,double> &cache)
{
    //check the value whether alrady in cache
    auto cachedIt = cache.find(n);
    if(cachedIt != cache.end()){
        //cachedIt is a iterator that points to element in map
        //ecah element in map is a pair
        return cachedIt->second;
    }
    if (n == 0)
    {
        return 0.0;
    }
    double h = 0.0;
    for (int i = 0; i < n; i++)
    {
        h += (max(avg_bst_height(i, cache), avg_bst_height(n - i - 1, cache))) / n;
    }
    h++;
    cache[n] = h;
    return h;
}

int main()
{   
    map<int,double> cache;
    for(int i = 0; i < 1000; i++){
        cout << "H(" << i << ") == " << avg_bst_height(i, cache) << endl;
    }

    return 0;
}