#include<iostream>
#include<vector>

using namespace std;

// Divide and Conquer Algorithm
/*
Quick Sort: Take a pivot (can take randomly, example, a[0]) and put the pivot in it's sorted position
How to do it?
Start a pointer from low and a pointer from high. 
Find first occurrence of a number > pivot from low
Find first occurrence of a number <= pivot from high
Swap these two numbers.
Finally swap j and pivot position.
This ensures that pivot number gets to the position it should be in after whole array is sorted.
The above procedures ensure that numbers left of pivot are less than pivot, and right of pivot are >= pivot.
So, pivot is our partition index now, and after that apply quicksort to the left of pivot separately, and right of pivot as well.
Recursive method.
*/

int findIdx(vector<int> &a, int low, int high)
{
    int pivot = a[low];
    int i = low, j = high;

    while(i < j)
    {
        while(i < high && a[i] <= pivot) ++i;
        while(j > low && a[j] > pivot) --j;

        if(i < j) swap(a[i], a[j]);
    }

    swap(a[low], a[j]);

    return j;
}

void quick_sort(vector<int> &a, int low, int high)
{
    if(low < high)
    {
        int partitionIdx = findIdx(a, low, high);
        quick_sort(a, low, partitionIdx - 1);
        quick_sort(a, partitionIdx + 1, high);
    }
}

int main()
{
    vector<int> a = {13, 46, 24, 52, 20, 9};

    quick_sort(a, 0, 5);

    for(int i = 0; i<6; i++)
    cout << a[i] << "\t";
}