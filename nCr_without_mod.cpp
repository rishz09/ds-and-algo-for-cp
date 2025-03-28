// calculating nCr without MOD, ie, when final result won't result in overflow, but individual factorial may result in so
// eg: 30 C 15
// 30! indiviually will result in overflow

#include <iostream>

using namespace std;

long long nCr(int n, int r)
{
    if(r > n - r)
    r = n - r;

    long long res = 1;
    for(int i=0; i<r; i++)
    {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

int main()
{
    int n = 2;
    int r = 2;

    cout << nCr(n, r) << endl;
    return 0;
}