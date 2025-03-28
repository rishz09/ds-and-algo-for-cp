// https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees
// 1D fenwick tree
// Notes to be uploaded as a drive link for my reference
#include <bits/stdc++.h>

using namespace std;

class FenwickTree
{
    public:
    int maxSize;
    vector<int> BIT;

    FenwickTree(int n)
    {
        maxSize = n;
        BIT.resize(maxSize + 1, 0);
    }

    // it is being assumed that update and sum queries receive "idx" as 1-based
    // indexing. Do put the incremented index when calling the functions

    void initialize(int idx, vector<int> &arr)
    {
        int val = arr[idx - 1];
        int i = idx;

        while(i <= maxSize)
        {
            BIT[i] += val;
            i += (i & (-i));
        }
    }

    void update(int idx, int val, vector<int> &arr)
    {
        int diff = val - arr[idx - 1];
        arr[idx - 1] = val;

        int i = idx;
        while(i <= maxSize)
        {
            BIT[i] += diff;
            i += (i & (-i));
        }
    }

    int getSum(int idx)
    {
        int sum = 0;
        int i = idx;

        while(i > 0)
        {
            sum += BIT[i];
            i -= (i & (-i));
        }

        return sum;
    }

    // binary search on BIT
    // this is equivalent to finding lower_bound on prefix sums array
    // like: find the first index where prefix sum becomes some given X
    // TC: O(log N), whereas normal binary search is O(log^2 N)
    // https://codeforces.com/blog/entry/61364

    int binary_search(int target)
    {
        // NOTE: This always returns 1 based indexing index
        int sum = 0, pos = 0;
        int LOGN = log2(maxSize);

        for(int i=LOGN; i>=0; i--)
        {
            if((pos + (1 << i)) < maxSize && (sum + BIT[pos + (1 << i)] < target))
            {
                sum += BIT[pos + (1 << i)];
                pos += (1 << i);
            }
        }

        return pos + 1;
    }
};

int main()
{
    int n = 16;
    vector<int> arr = {1,0,2,1,1,3,0,4,2,5,2,2,3,1,0,2};

    FenwickTree f(n);
    
    for(int i=0; i<n; i++)
    f.initialize(i + 1, arr);

    // f.update(3, 5, arr);
    // cout << f.getSum(5) - f.getSum(1) << endl;

    cout << f.binary_search(7) << endl;
    return 0;
}