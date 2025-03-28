#include<vector>
#include<iostream>

using namespace std;

void sieveNaive(int n)
{
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;

    for(int i=2; i<=n; i++)
    {
        if(isPrime[i])
        {
            for(int j=2*i; j<=n; j += i)
            isPrime[j] = false;
        }
    }

    for(int i=2; i<=n; i++)
    {
        if(isPrime[i])
        cout << i << " ";
    }
}

void sieveOfEratosthenes(int n)
{
    vector<bool> isPrime(n+1, true);
    isPrime[1] = false;
    
    // optimization
    // TC: O(Nlog(log N))
    for(int i=2; i * i <=n; i++)
    {
        // doing i * i <= n because all others will have been previously checked for in the j loop
        if(isPrime[i] == true)
        {
            // why start j from i * i?
            // Suppose i = 2. i will mark 4, 6, 8 ... etc as false
            // then i = 3. Should we start from 2 * 3? No, because 2 * 3 is already marked by 2
            // 3 * 3 is not marked. So start from there. Take more examples and you will understand
            for(int j = i*i; j <= n; j = j + i)
            isPrime[j] = false;
        }
    }

    cout << "Prime numbers upto " << n << " (inclusive):" << endl;
    for(int i=2; i<=n; i++)
    {
        if(isPrime[i])
        cout << i << endl;            
    }
}

int main()
{
    int n;
    cin >> n;

    //printing prime numbers upto n (inclusive)
    // sieveOfEratosthenes(n);
    sieveNaive(n);
}