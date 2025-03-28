// the following uses sieve to find smallest prime factor (spf) of every number
// this can be used for prime factorization in O(log n), which would naively be done in O(root n)
// How does this work?
// Consider 18
// spf(18) = 2
// 18 / 2 = 9
// spf(9) = 3
// 9 / 3 = 3
// spf(3) = 3
// This is where we stop

#include <iostream>
#include <vector>

using namespace std;

void findSPF(vector<int> &spf)
{
    int n = spf.size();
    for(int i=0; i<n; i++)
    spf[i] = i;

    for(int i=2; i*i<n; i++)
    {
        // means prime number
        if(spf[i] == i)
        {
            for(int j=i*i; j<n; j += i)
            {
                if(spf[j] == j)
                spf[j] = i;
            }
        }
    }
}

void primeFactorization(int n, vector<int> &spf)
{
    while(spf[n] != n)
    {
        cout << spf[n] << " ";
        n /= spf[n];
    }

    cout << spf[n] << endl;
}

int main()
{
    int n = 10000 + 1;
    vector<int> spf(n);

    findSPF(spf);

    // for(int i=0; i<30; i++)
    // cout << i << " " << spf[i] << endl;
    primeFactorization(42, spf);

    return 0;
}