#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int solve(int i, int prevIdx, vector<int> &nums, vector<vector<int>> &dp)
    {
        if(i == nums.size())
        return 0;

        // doing prevIdx + 1 because we want to accomodate prevIdx = -1 case as that stores our final answer
        if(dp[i][prevIdx + 1] != -1)
        return dp[i][prevIdx + 1];

        // not take
        int maxi = solve(i + 1, prevIdx, nums, dp);

        // take
        if(prevIdx == -1 || nums[i] > nums[prevIdx])
        maxi = max(maxi, 1 + solve(i + 1, i, nums, dp));

        return dp[i][prevIdx + 1] = maxi;
    }

    int lengthOfLIS(vector<int>& nums) 
    {
        int n = nums.size();

        // shift of the inside indices (as prevIdx is initally -1)
        // dp[i][prevIdx] = LIS starting from nums[i], where previous considered number = nums[prevIdx - 1]
        // vector<vector<int>> dp(n + 1, vector<int> (n + 1, -1));
        // return solve(0, -1, nums, dp);

        // tabulation
        // vector<vector<int>> dp(n + 1, vector<int> (n + 1, 0));

        // for(int i=n-1; i>=0; i--)
        // {   
        //     // prevIdx can't be n - 1 obviously
        //     for(int prevIdx = n - 2; prevIdx >= -1; prevIdx--)
        //     {
        //         // not take
        //         int maxi = dp[i + 1][prevIdx + 1];  // need prevIdx + 1 as we are doing index shifting

        //         // take
        //         if(prevIdx == -1 || nums[i] > nums[prevIdx])
        //         maxi = max(maxi, 1 + dp[i + 1][i + 1]);

        //         dp[i][prevIdx + 1] = maxi;
        //     }
        // }

        // return dp[0][-1 + 1];
        // -------------- Tabulation Ends Here ---------------------

        // Another Iterative approach also exists to get LIS
        // This is more space efficient as it uses 1D DP.
        // Each index has a dp cell.
        // For index i, we consider all indices from 0 to i - 1, and
        // after having the greater than condition as true, we check, with which
        // index is LIS produced. We then update dp[i] with the max length produced.
        // NOTE: This method is used to print the LCS. Backtracking is used with this to get it
        
        // initally, max LIS for every index is the number itself
        vector<int> dp(n, 1);
        int maxi = 1;
        for(int i=1; i<n; i++)
        {
            for(int j=0; j<i; j++)
            {
                if(nums[j] < nums[i])
                dp[i] = max(dp[i], 1 + dp[j]);
            }

            maxi = max(maxi, dp[i]);
        }

        // note that max might not be stored in dp[n - 1]. Suppose is nums[n - 1] is the smallest
        // number in array, it won't store the LIS length.
        // So we need to iterate over entire array, as a result the maxi variable is used.
        return maxi;
    }
};

int main()
{
    vector<int> nums = {10,9,2,5,3,7,101,18};

    Solution s;
    int res = s.lengthOfLIS(nums);
    cout << res << endl;

    // LINK FOR PRINTING LIS: https://www.geeksforgeeks.org/problems/printing-longest-increasing-subsequence/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=printing-longest-increasing-subsequence
    // Its basically improvisation on 1D DP approach
}