#include <iostream>
#include <vector>

using namespace std;

int solve(int i, int j, string &s, string &t, vector<vector<int>> &dp)
{
    if(i == s.length() || j == t.length())
    return 0;
    
    int res;
    if(s[i] == t[j])
    res = 1 + solve(i + 1, j + 1, s, t, dp);

    else
    res = 0;

    solve(i + 1, j, s, t, dp);
    solve(i, j + 1, s, t, dp);

    return dp[i][j] = res;
}

vector<vector<int>> tabulation(string &s, string &t)
{
    int l1 = s.length(), l2 = t.length();
    // move from right to left since our recurrence relation involved getting
    // dp[i + 1][j + 1]. So we need rightwards stuff first

    vector<vector<int>> dp(l1, vector<int> (l2, 0));
    for(int i=0; i<l1; i++)
    {
        if(s[i] == t[l2 - 1])
        dp[i][l2 - 1] = 1;
    }

    for(int j=0; j<l2; j++)
    {
        if(s[l1 - 1] == t[j])
        dp[l1 - 1][j] = 1;
    }

    for(int i=l1-2; i>=0; i--)
    {
        for(int j=l2-2; j>=0; j--)
        {
            if(s[i] == t[j])
            dp[i][j] = 1 + dp[i + 1][j + 1];

            else
            dp[i][j] = 0;
        }
    }

    return dp;
}

int main()
{
    string s = "12321";
    string t = "32147";

    int l1 = s.length(), l2 = t.length();

    // dp[i][j] = length of substring if checking starts from s[i] and t[j]
    vector<vector<int>> dp(l1, vector<int> (l2, -1));

    solve(0, 0, s, t, dp);

    int maxi = 0;
    for(int i=0; i<l1; i++)
    {
        for(int j=0; j<l2; j++)
        {
            cout << dp[i][j] << " ";
            maxi = max(maxi, dp[i][j]);
        }

        cout << endl;
    }

    cout << "------x------" << endl;

    vector<vector<int>> dp2 = tabulation(s, t);
    for(int i=0; i<l1; i++)
    {
        for(int j=0; j<l2; j++)
        {
            cout << dp2[i][j] << " ";
            maxi = max(maxi, dp2[i][j]);
        }

        cout << endl;
    }

    return 0;
}