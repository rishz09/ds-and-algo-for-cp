// Given a set size of n and number of bits that need to be EXACTLY set
// in every subset, k, Gosper's Hack generates ONLY the subsets that have
// EXACTLY k bits set in a set of size n
// TC: O(nCk), as opposed to O(2^n) naive subset generation

// https://programmingforinsomniacs.blogspot.com/2018/03/gospers-hack-explained.html
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// find_by_order, order_of_key
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

#define Sort(arr) sort(arr.begin(), arr.end())
#define SortRev(arr) sort(arr.begin(), arr.end(), greater<int>())
#define nl "\n"
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef long long ll;

void gospersHack(int k, int n)
{
    // rightmost k set bits
    int mask = (1 << k) - 1;
    int limit = (1 << n);

    while(mask < limit)
    {
        bitset<6> b(mask);
        cout << b << nl;

        int c = mask & -mask;
        int r = mask + c;
        mask = (((r ^ mask) >> 2) / c) | r;
    }
}

int main()
{
    int n = 6, k = 3;
    gospersHack(k, n);

    return 0;
}