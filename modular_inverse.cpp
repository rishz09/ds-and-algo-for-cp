#include <iostream>
#include <math.h>

using namespace std;

// also known as modular multiplicative inverse 
// Modular inverse can also be found out using Fermat's Little Theorem, ie, using Binary Exponentiation (this is easier to understand)

int extended_euclidean(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = extended_euclidean(b, a % b, x1, y1);

    x = y1;
    y = x1 - (y1 * floor(a / b));  // equivalent to just a / b in int terms

    return g;
}

int get_modular_inverse(int a, int m)
{
    int x, y;
    int g = extended_euclidean(a, m, x, y);

    if(g != 1)
    return -1;

    x = (x % m + m) % m;
    return x;
}


// Fermat's Little Theorem:
// If p is a prime number, then for any integer a, the number [(a^p) – a] is an integer multiple of p. 
// ie, a^p % p = a

// Special case (which is actually used for modular inverse):
// If a is not divisible by p, Fermat’s little theorem is equivalent to the statement that (a^(p-1)) - 1 is an integer multiple of p.
// ie, (a^(p - 1)) % p = 1
// Then, (a ^ (p - 2)) % p = a^(-1) = modular inverse of a
// a^(p - 2) can be found out in O(log p) TC using binary exponentiation

int modular_inverse_binary_exponentiation(long long a, int p)
{
    int res = 1;
    int k = p - 2;

    while(k > 0)
    {
        if(k % 2 == 1)
        res = (res * a) % p;

        a = (a * a) % p;
        k /= 2;
    }

    return res;
}

int main()
{
    int a = 0, MOD = 1e9 + 7;
    // int mod_inv = get_modular_inverse(a, MOD);
    // cout << "Modular inverse using extended euclidean: " << mod_inv << endl;

    int mod_inv = modular_inverse_binary_exponentiation(a, MOD);

    // proving that modInv(a * b) % MOD = (modInv(a) * modInv(b)) % MOD (associative property)
    int part1 = 2, part2 = 3;
    long long res1 = modular_inverse_binary_exponentiation(part1, MOD), res2 = modular_inverse_binary_exponentiation(part2, MOD);
    int res = (res1 * res2) % MOD;

    cout << "Modular inverse using binary exponentation: " << mod_inv << endl;
    cout << "After breaking number into factors: " << res << endl;

    return 0;
}