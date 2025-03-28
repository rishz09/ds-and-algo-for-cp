#include<algorithm>
#include<iostream>

using namespace std;

struct Job 
{ 
    int id;	 // Job Id 
    int dead; // Deadline of job 
    int profit; // Profit if job is over before or on deadline 
};

bool comp(Job j1, Job j2)
    {
        if(j1.dead > j2.dead)
        return true;
        
        else if(j1.dead == j2.dead)
        {
            if(j1.profit > j2.profit)
            return true;
            
            else
            return false;
        }
        
        else
        return false;
    }

int main()
{
    Job arr[] = {
        {1, 2, 100},
        {2, 1, 19},
        {3, 2, 27},
        {4, 1, 25},
        {5, 1, 15}
        };

    sort(arr, arr + 5, comp);

    for(int i=0; i<5; i++)
    cout << arr[i].id << " " << arr[i].dead << " " << arr[i].profit << endl;
        
    return 0;
}