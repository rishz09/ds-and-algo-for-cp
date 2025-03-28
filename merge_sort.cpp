#include<iostream>
#include<vector>

using namespace std;

/*
Divide the array into equal halves till each half has one element, then merge in bottom up approach of recursion tree,
where each merge operation has the merged array sorted.
*/

void merge(vector<int> &a, int low, int mid, int high)
{
    vector<int> temp(high - low + 1, -1e9);
    int left = low;
    int right = mid + 1;
    int i = 0;

    while(left <= mid && right <= high)
    {
        if(a[left] <= a[right])
        {
            temp[i] = a[left];
            ++left;
        }

        else
        {
            temp[i] = a[right];
            ++right;
        }

        ++i;
    }

    while(left <= mid)
    {
        temp[i] = a[left];
        ++i;
        ++left;
    }

    while(right <= high)
    {
        temp[i] = a[right];
        ++i;
        ++right;
    }

    i = 0;
    for(int j = low; j<=high; j++)
    a[j] = temp[i++];
}

void merge_sort(vector<int> &a, int low, int high)
{
    if(low == high) return;

    int mid = (low + high) / 2;
    merge_sort(a, low, mid);
    merge_sort(a, mid + 1, high);

    merge(a, low, mid, high);
}

int main()
{
    vector<int> a = {13, 46, 24, 52, 20, 9};

    merge_sort(a, 0, 5);

    for(int i = 0; i<6; i++)
    cout << a[i] << "\t";
}