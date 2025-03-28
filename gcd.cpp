#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int gcd_custom(int a, int b) 
{
    if(b == 0)
    return a;

    else
    return gcd_custom(b, a % b);
}

int main()
{
    int a = 3, b = 4;
    cout << gcd_custom(a, b) << endl;
    cout << __gcd(3, 4) << endl;

    return 0;
}