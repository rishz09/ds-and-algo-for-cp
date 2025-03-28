// alternative to kadane's algorithm is to subtract current prefix sum with
// the minimum seen prefix sum yet (great concept)

#include <iostream>
#include <vector>

using namespace std;

int findMinSubArraySum(vector<int> &arr)
{
    int n = arr.size();
    int curMin = 0, mini = INT_MAX;
    
    for(int &ele: arr)
    {
        curMin = min(ele, curMin + ele);
        mini = min(mini, curMin);
    }

    return mini;
}

int findMaxSubArraySum(vector<int> &arr)
{
    int n = arr.size();
    int curMax = 0, maxi = INT_MIN;

    for(int &ele: arr)
    {
        // what is the logic behind this step?
        // consider previous subarray summed up to negative numbers
        // Let the sum be -5.
        // Now, consider current arr[i] > -5. Consider it to be -2
        // Then, it makes no sense to consider curMax + ele (arr[i]), since it will just reduce the subarray sum even more
        // - 5 - 2 = -7
        // Instead, just consider starting the subarray from arr[i] itself, since it will bypass the negative effect of the previous subarray.
        curMax = max(ele, curMax + ele);
        maxi = max(maxi, curMax);
    }

    return maxi;
}

int main()
{
    vector<int> arr = {-1,-1,1,1,-1,1,1,1};
    cout << findMaxSubArraySum(arr) << endl;

    vector<int> arr2 = {10, -5, 2, -3, 5};
    cout << findMinSubArraySum(arr2) << endl;
    
    return 0;
}