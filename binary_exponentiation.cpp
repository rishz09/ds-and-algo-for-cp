#include <iostream>

using namespace std;

// naive way takes O(b) TC. This algo takes O(log b) TC
int power(int a, int b)
{
    if(b == 0)
    return 1;

    int temp = power(a, b/2);
    int res = temp * temp;

    if(b % 2 == 1)
    res *= a;

    return res;
}

int powerIterative(int a, int b)
{
    // what is the intuition behinid iterative solution?
    // consider b = 11, a = 3
    // we need 3 ^ 11
    // now binary of 11 = 1011
    // We use the power of index position of the set bits
    // This basically means, for a index position i, contribution to product = 3 ^ (pow(2, i))
    // 1011 -> (3 ^ (2^3)) * 1 * (3 ^ (2^1)) * (3 ^ (2^0))
    // -> 3^8 * 3^2 * 3
    // -> 3^11
    // If we observe the loop, a is calculating 3 ^ (2^i)
    // And, if condition checks if we want to include a as a contribution to the product or not

    int res = 1;
    while(b > 0)
    {
        if(b % 2 == 1)
        res *= a;

        a *= a;
        b /= 2;
    }

    return res;
}

long long powerIterativeModular(long long a, long long b, int MOD)
{
    a %= MOD;
    long long res = 1;
    while(b > 0)
    {
        if(b % 2 == 1)
        res = (res * a) % MOD;

        a = (a * a) % MOD;
        b /= 2;
    }

    return res;
}

int main()
{
    // need to include modulo if res needs to be modulo-ed
    cout << power(3, 11) << endl;
    cout << powerIterative(3, 11) << endl;
    cout << powerIterativeModular(3, 11, (int)(1e9 + 7));  // for a^b mod M
}
