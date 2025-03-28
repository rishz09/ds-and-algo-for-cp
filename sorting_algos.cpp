#include<iostream>
#include<vector>

using namespace std;

/*
Selection sort: Select the largest element and swap it in first pos. Then search for largest element from [1, n - 1] and
swap it in second pos. Continue this till [n - 2, n - 1] because [n - 1] will be sorted in the final step.
*/

void selection_sort(vector<int> &a, int n)
{
    for(int i=0; i<n-1; i++)
    {
        int min = INT_MAX, idx = -1;
        for(int j=i; j<n; j++)
        {
            if(a[j] < min)
            {
                min = a[j];
                idx = j;
            }
        }

        int temp = a[i];
        a[i] = a[idx];
        a[idx] = temp;
    }
}

/*
Bubble sort: Pick pairs and swap if element[i + 1] < element[i]. In first step, largest element will go to arr[n - 1]
In next step, second largest element will go to arr[n - 2], so reduce search space by 1 from the right, with every iteration.
*/

void bubble_sort(vector<int> &a, int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(a[j] < a[j+1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

// brings correct element to the left side first, instead of right
void bubble_sort2(vector<int> &a, int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=n-1; j>=i+1; j--)
        {
            if(a[j] > a[j - 1])
            swap(a[j], a[j - 1]);
        }

        for(int i=0; i<n; i++)
        cout << a[i] << " ";
        cout << endl;
    }    
}

/*
Insertion sort: Start from range [0, 1] and check if they are sorted. If not, swap.
Step 2: [0, 2] sort space. If not sorted, swap positions one by one.
Do till Step n-1, where the last element will be checked against every other element.
Example: If last element is not sorted and it should be in position 1, then swap positions one by one from right to left.
*/

void insertion_sort(vector<int> &a, int n)
{
    for(int i=1; i<n; i++)
    {
        if(a[i] < a[i - 1])
        {
            int j = i;
            while(j > 0 && a[j] < a[j - 1])
            {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;

                --j;
            }
        }
    }
}

int main()
{
    vector<int> a = {13, 46, 24, 52, 20, 9};
    vector<int> b = {9, 20, 52, 24, 46, 13};

    // selection_sort(a, 6);
    // bubble_sort(b, 6);
    // insertion_sort(a, 6);

    bubble_sort2(b, 6);

    // for(int i=0; i<6; i++)
    // cout << a[i] << "\t";

    return 0;
}