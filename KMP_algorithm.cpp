// efficient string matching algorithm, based on LPS
// LPS - longest prefix suffix

// Consider txt = ABABCABCABABABD
// pattern = ABABD

// consider we are idx = 4. C and D do not match
// In the naive method, we would have started the whole matching from i = 1
// But, we do not need to do so. Why?

// Consider the characters before D in pattern. We have ABAB
// i is the pointer to text, and j is the pointer to pattern
// Both are 4 currently, and there's a mismatch.

// Since we have come to j = 4, we know that there exists 2 ABs consecutively in txt.
// So, what we can do is, instead of making j = 0, we can start from j = 2
// Why? Because AB will always match before, and now, we keep i = 4 and match for j = 2

// The approach was this:
// For j = 4, since there is mismatch, go to j = 4 - 1 = 3, and check for the longest
// prefix between [0, 3], for which we have equal suffix.
// The prefix is [0, 1] (prefix) and [2, 3] (suffix).

// So, we know that the prefix will match, as a result, we will start from end of 
// prefix + 1, ie, j = 2

// This is the role of LPS, ie, longest prefix suffix for each index of pattern. We reduce the length we take to match.

// LPS array stores the length of the prefix and suffix that matches. So basically, if length = 2, we have prefix match for [0, 1] and we start next character match checking
// from j = 2 itself.

// LPS can for any index can overlap, but there needs to be atleast one non overlapping character to each prefix and suffix

// The algorithm to find LPS is this:
// initially, LPS[0] = 0
// for index j, we go to j - 1 and get the LPS. Let the lps be x. We check if pattern[j] == pattern[x]. If equal, then we make LPS[j] = LPS[j - 1] + 1
// consider ABCABC
// we have LPS[4] = 2
// For LPS[5], we check for pattern[5] == pattern[2], yes
// So, LPS[5] = 2 + 1 = 3

// Now, if character didn't match, then it would have meant that we have come to far from the start. Let LPS[j - 1] = len. If pattern[len] != pattern[j],
// we make len = LPS[len - 1] and check for match again. If finally len becomes 0, make LPS[j] = 0

// consider pattern: AAAAC
// LPS[0] = 0 (always 0), len = 0
// LPS[1] = 1, len = 1 
// LPS[2] = 2 (overlap) -> [0, 1] (prefix), [1, 2] (suffix), len = 2
// LPS[3] = 3, len = 3
// LPS[4] = 0

// Steps for LPS[4] -> pat[4] != pat[3], so, len = LPS[len - 1] = 2
// pat[4] != pat[2], so len = LPS[2 - 1] = 1
// pat[4] != pat[1], so len = 0
// finally, pat[4] = 0, len = 0

// This LPS array is used extensively for string matching using KMP Algo
// Consider mismatch at i and j.
// Then, we go to j - 1 and ask to check from j = LPS[j - 1] (after the matched prefix)
// If still not match, go back again. If we reach j = 0 and still no match, we simply increment i by 1 and start the same drill

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void findLPS(string &pattern, vector<int> &lps)
{
    int n = pattern.length();
    int len = 0;

    lps[0] = 0;

    int i = 1;
    while(i < n)
    {
        if(pattern[i] == pattern[len])
        {
            ++len;
            lps[i] = len;
            ++i;
        }

        else
        {
            if(len != 0)
            len = lps[len - 1];  // same as doing len = len - 1

            else
            {
                lps[i] = 0;
                ++i;
            }
        }
    }
}

vector<int> KMPSearch(string &s, string &pattern)
{
    // this particular function finds all the starting indices in s, where the substring matches with pattern. we can obviously modify it
    // to find only for one index

    int n = s.length(), m = pattern.length();

    vector<int> res;
    vector<int> lps(m);

    findLPS(pattern, lps);

    int i = 0, j = 0;
    while(i < n)
    {
        if(s[i] == pattern[j])
        {
            ++i;
            ++j;
        }

        // we have matched the string
        if(j == m)
        {
            res.push_back(i - m);
            j = lps[j - 1];
        }

        else if(s[i] != pattern[j])
        {
            if(j != 0)
            j = lps[j - 1];

            else
            ++i;
        }
    }

    return res;
}

int main()
{
    string s = "geeksforgeeks";
    string pattern = "geek";

    vector<int> res = KMPSearch(s, pattern);

    for(int &ele: res)
    cout << ele << " ";

    cout << endl;
}