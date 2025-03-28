/* 
THIS IS VERY IMPORTANT TO ME AS I HAD CONFUSION WITH AN EDGE CASE
The confusion was that, what if the first k inserted elements are the k smallest elements itself?
Many yt videos simply pushed and popped at every iteration.

But understand this.
Suppose I pushed k smallest elements at first.
Next, I push an element. It is bound to be greater than the k smallest elements.
Now, priority queue size will also be (k + 1), so one needs to be popped out.
So, definitely the ONLY element, which does not belong to k smallest elements, will be popped out.

This situation only works because we are popping out ONLY when size of pq becomes k + 1.
If we had popped out before inserting an extra element, definitely one of the k smallest elements would have popped out,
and answer would have been wrong.

Workaround: If we wish to pop out before inserting the (k + 1)th element, simply add a condition.
If the element to be inserted is less than pq.top(), then pq.pop() and insert it.
Otherwise, just ignore because we already have smaller elements.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 4;

    priority_queue<int> pq;
    vector<int> res;

    for(int i=0; i<10; i++)
    {
        if(pq.size() < k)
        pq.push(a[i]);
        
        else if(pq.size() == k)
        {
            pq.push(a[i]);
            pq.pop();
        }
    }

    while(!pq.empty())
    {
        res.push_back(pq.top());
        pq.pop();
    }

    for(int &ele: res)
    cout << ele << " ";
    cout << endl;

    // workaround case
    res = vector<int> ();
    for(int i=0; i<10; i++)
    {
        if(pq.size() < k)
        pq.push(a[i]);

        else if(pq.size() == k)
        {
            if(a[i] < pq.top())
            {
                pq.pop();
                pq.push(a[i]);
            }

            else
            continue;
        }
    }

    while(!pq.empty())
    {
        res.push_back(pq.top());
        pq.pop();
    }

    for(int &ele: res)
    cout << ele << " ";
    cout << endl;
}