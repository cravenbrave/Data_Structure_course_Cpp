#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
using namespace std;
#define range 100000  // 控制数组的大小
int myrandom(int a[]) //随机填充数组
{
    int max = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i < range; i++)
    {
        a[i] = rand() % range + 1;
        if (a[i] > max)
            max = a[i];
    }
    return max;
}
int Max_bit(int a) //求最大数的位数
{
    return a < 10 ? 1 : 1 + Max_bit(a / 10);
}

//a complicated way to find the digits of max number
// int max(int A[], int n) //辅助函数，求数据的最大位数
// {
//     int maxData = A[0];
//     for (int i = 1; i < n; ++i)
//     {
//         if (maxData < A[i])
//             maxData = A[i];
//     }
//     int cout = 1;
//     int p = 10;
//     while (maxData >= p)
//     {
//         maxData /= 10;
//         ++cout;
//     }
//     return cout;
// }

void RadixSort(int a[], int max_bit) //基数排序
{
    queue<int> temp[10];
    int mod = 10;
    int div = 1;
    int j = 0;
    int num = 0;
    for (int i = 0; i < max_bit; i++, mod *= 10, div *= 10)
    {
        //最开始取最右边一位 11%10 = 1 1/1 = 1
        //再取第二位e.g.122%100 = 22  22/10 = 2      101%100 = 1； 1/10 = 0
        for (j = 0; j < range; j++)
        {
            num = (a[j] % mod) / div;
            temp[num].push(a[j]);
        }

        //再把每个vector的值从第一个开始取放回原array
        int pos = 0;
        for (j = 0; j < 10; j++)
        {

            while (!temp[j].empty())
            {

                a[pos++] = temp[j].front();
                temp[j].pop();
            }
        }
    }
}
int main()
{
    clock_t start, end; // 用于测试 用时
    start = clock();
    freopen("out基数排序.txt", "w", stdout); // 重定向
    int a[range];

    int max = myrandom(a);
    int bit_max = Max_bit(max);

    RadixSort(a, bit_max);
    for (int i = 0; i < range; i++)
    {
        printf("%5d ", a[i]);
        if ((i + 1) % 50 == 0)
            printf("\n");
    }
    end = clock();
    cout << range << "个数据通过基数排序耗时：" << (float)(end - start) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}