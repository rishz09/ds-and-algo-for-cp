// sparse table is used for answering static range queries.
// static as in: the array is not changed / mutated in between queries

// preprocessing is done in O(n log n) TC
// per query answering is done in O(1) TC

// the whole concept of sparse table is using powers of 2 to represent intervals.
// just like how numbers can be represented as powers of 2, interval sizes can be represented in powers of 2 as well.

// consider interval [2, 10] (inclusive indices)
// here, size of interval = 9 = 2^3 + 2^0

// usages: Range Maximum / Minimum Queries, range GCD, etc.
// we solve here for Range Minimum Query

// the table is m[i][j]
// i = starting index, j = power of 2

// what does this mean?
// m[i][j] = minimum number in the interval which begins at index i and has length of 2^j
// so, m[3][2] = minimum number in the interval [3, 3 + 2^2 - 1] = [3, 3 + 4 - 1] = [3, 6]

// we build m[i][j] using the immediate lower power (j - 1) of 2.
// consider m[2][3]. This interval spans from [2, 9].

// using smaller powers, we can build m[2][3] as:
// m[2][3] = min(m[2][2], m[6][2]) -> this spans from [2, 5] U [6, 9]

// so this involves dp. We calculate minimums for every lower powers, and then move on to higher powers.

// how many powers to include?
// consider n = 100,000.
// Then 2^16 = 65,536 and 2^17 = 131,072

// so, we need to run j till 16 (inclusive) since 17 crosses any valid subarray range.
// however, n is a perfect power of 2, for eg, 1024, then obviously till 10 and not 9.

// for a specific power j, till which index to run the build up?
// till the index i such that, i + 2^j - 1 (end of the interval) < n

// so, if n = 9 and we are building for j = 2,
// for j = 2, the last index we consider is 5, since 5 + 2^2 - 1 = 8.
// If we take 6, we reach 9 and it is not a valid index. Hence, till 5.


// Query Answering:
// It is quite intuitive to think that for the required range, we will break it down into powers of 2.
// If our range is [3, 12], we do [3, 10] + [10, 11] + [12, 12]
// so, minimum in this range = min(m[3][3], m[10][1], m[12][0])

// this is okay, but for huge subarray lengths, this breaking into powers of 2 will be O(log n) per query.
// But as said above, query answering is O(1).

// So how to do it?
// Consider the same interval [3, 12].
// Interval size = 10
// Previous lower power of 2 = 8 = 2^3

// We can get the minimum using JUST the previous lower j wrt the interval size
// Over here, interval size = 10 and j = 3
// How?

// For [3, 12], we can get minimum as, 
// minimum = min(m[3][3] + m[5][3])
// so the intervals in consideration are [3, 10] and [5, 12]
// Why does this work?
// Because it doesn't matter if there is interval overlap. 
// In the end, we will obviously get minimum for [3, 12] only.
// Hence, O(1) query answering

// For video and problems: https://www.youtube.com/watch?v=0jWeUdxrGm4

#include <bits/stdc++.h>

using namespace std;

// for n = 100000, we need max j = 16
int m[100000][17];

void printMinimums(int n)
{
    int LOG = floor(log2(n));

    for(int j=0; j<=LOG; j++)
    {
        cout << "J: " << j << endl;
        for(int i=0; i + (1 << j) - 1 < n; i++)
        {
            int left = i, right = i + (1 << j) - 1;
            cout << "[" << left << ", " << right << "] = " << m[left][j] << endl;
        }
        
        cout << endl;
    }
}

int main()
{
    int n = 8;
    // cin >> n;

    vector<int> a = {2, 3, 4, 5, 3, 1, 1, 3};

    int LOG = floor(log2(n));

    // Preprocessing
    for(int i=0; i<n; i++)
    m[i][0] = a[i];

    for(int j=1; j<=LOG; j++)
    {
        for(int i=0; i + (1 << j) - 1 < n; i++)
        m[i][j] = min(m[i][j - 1], m[i + (1 << (j - 1))][j - 1]);
    }


    // Query answering
    int L = 1, R = 3;
    int len = R - L + 1;

    int k = floor(log2(len));  // power of 2 just before the length. Like for len = 10, we have 3 (2^3 = 8)

    int mini = min(m[L][k], m[R - (1 << k) + 1][k]);
    cout << mini << endl;

    // printMinimums(n);

    return 0;
}

