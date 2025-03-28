#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

// Longest Common Subsequence, not substring

int solve(int i, int j, string &s1, string &s2, vector<vector<int>> &dp)
{
    if(i < 0 || j < 0)
    return 0;

    if(dp[i][j] != -1)
    return dp[i][j];

    // character match case
    if(s1[i] == s2[j])
    return dp[i][j] = 1 + solve(i - 1, j - 1, s1, s2, dp);

    // not match case
    return dp[i][j] = max(solve(i - 1, j, s1, s2, dp), solve(i, j - 1, s1, s2, dp));
}

int solve2(int i, int j, string &s1, string &s2, vector<vector<int>> &dp)
{
    if(i == 0 || j == 0)
    return 0;

    if(dp[i][j] != -1)
    return dp[i][j];

    // character match case
    if(s1[i - 1] == s2[j - 1])
    return dp[i][j] = 1 + solve2(i - 1, j - 1, s1, s2, dp);

    // not match case
    return dp[i][j] = max(solve2(i - 1, j, s1, s2, dp), solve2(i, j - 1, s1, s2, dp));
}

vector<vector<int>> longestCommonSubsequence(string s1, string s2) 
{
    int m = s1.size(), n = s2.size();

    // dp[i][j] represents LCS in s1[0...i] and s2[0...j] (inclusive indices)
    // vector<vector<int>> dp(m, vector<int> (n, -1));
    // return solve(m - 1, n - 1, s1, s2, dp);

    // for tabulation, base case is tricky as we have i < 0 and j < 0.
    // So, we need to do one right shift of indices
    // Then, dp[i][j] represents LCS in s1[0...i-1] and s2[0...j-1]
    // And our base case becomes i == 0 || j == 0.
    // But, to access string character, we obviously need to do s1[i - 1] and s2[j - 1]

    // vector<vector<int>> dp(m + 1, vector<int> (n + 1, -1));
    // return solve2(m, n, s1, s2, dp);

    // tabulation with index shift
    vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));
    for(int i=0; i<=n; i++)
    dp[0][i] = 0;

    for(int i=0; i<=m; i++)
    dp[i][0] = 0;

    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            // character match case
            if(s1[i - 1] == s2[j - 1])
            dp[i][j] = 1 + dp[i - 1][j - 1];

            else
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp;

    // can also space optimize it as we only require only previous row at max, as seen from the formula
}

void findLCS(int i, int j, string &temp, string &s1, string &s2, vector<vector<int>> &dp, 
set<string> &st, unordered_set<string> &stateTrack)
{
    if(i == 0 || j == 0)
    {
        string t = temp;
        reverse(t.begin(), t.end());
        st.insert(t);
        return;
    }
        
    string key = to_string(i) + " " + to_string(j) + " " + temp;
    if(stateTrack.find(key) != stateTrack.end())
    return;
        
    stateTrack.insert(key);
    
    if(s1[i - 1] == s2[j - 1])
    {
        temp += s1[i - 1];
        findLCS(i - 1, j - 1, temp, s1, s2, dp, st, stateTrack);
        temp.pop_back();
    }
        
    else
    {
        if(dp[i - 1][j] == dp[i][j - 1])
        {
            findLCS(i - 1, j, temp, s1, s2, dp, st, stateTrack);
            findLCS(i, j - 1, temp, s1, s2, dp, st, stateTrack);
        }
    
        else if(dp[i][j - 1] > dp[i - 1][j])
        findLCS(i, j - 1, temp, s1, s2, dp, st, stateTrack);
    
        else
        findLCS(i - 1, j, temp, s1, s2, dp, st, stateTrack);
    }
}

int main()
{
    // string s1 = "abcde";
    // string s2 = "bdgek";

    string s1 = "abaaa";
    string s2 = "baabaca";

    int m = s1.length(), n = s2.length();

    vector<vector<int>> dp = longestCommonSubsequence(s1, s2);

    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
        cout << dp[i][j] << " ";
        cout << endl;
    }
    
    cout << endl;

    // Now, we can have complete DP table (note that, in recursion, the DP table isn't fully filled, unlike tabulation)
    // We can use this table to backtrack, in order to find LCS (one or many, if exists)
    // How?
    // Note that dp[i][j] corresponds to s1[i - 1] and s2[j - 1] characters at max
    // Now, look at the dp formula:
    // If s1[i - 1] = s2[j - 1], then we CAME FROM dp[i - 1][j - 1]
    // If not equal, then we CAME FROM max(dp[i - 1][j], dp[j][i - 1])
    
    // So, start at dp[m][n] and backtrack, till indices are lesser than minimum string index.
    // This will give LCS

    // Now, it might happen that there are multiple LCS
    // In this case, we need recursion for backtracking.
    // Multiple LCS will occur when dp[i - 1][j] = dp[j][i - 1] when s1[i - 1] != s2[j - 1]

    string temp = "";
    set<string> st;

    // need to further apply memoization on findLCS to prevent TLE
    // Our changing variables are i, j, and temp string.
    // If all these 3 states are found the same in any next iteration, we skip it.
    // We skip it, because we know that if this state has already been achieved, and if we find it again, it will give us redundant (same) LCS
    // But that doesn't mean that we can remove the set to store strings, because traversing from other pathways may also lead to the same string
    unordered_set<string> stateTrack;
    findLCS(m, n, temp, s1, s2, dp, st, stateTrack);

    vector<string> res(st.begin(), st.end());
    for(string &s: res)
    cout << s << endl;
}