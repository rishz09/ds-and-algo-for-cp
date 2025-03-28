/*
Uses a O(V * (V + E)) solution and does BFS from every node
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestCycle(int &start, int &n, vector<vector<int>> &adj, int curMin)
    {
        vector<int> breadth(n, -1);

        queue<int> q;
        q.push(start);
        breadth[start] = 1;

        while(!q.empty())
        {
            int size = q.size();
            
            // IMP: it was said that the first time a cycle is found, it is the minimum for that starting
            // node. But this may not be always true. Yes, if a cycle is found, the minimum length cycle
            // will be found in that breadth itself, but it isn't always true that the first cycle of that
            // breadth will be minimum. Many cycles may be present in the breadth, so we need to take
            // the minimum of all of them

            int mini = 1e9;

            while(size > 0)
            {
                int node = q.front();
                q.pop();    

                for(int &child: adj[node])
                {
                    // odd cycle and even cycle check respectively
                    if(breadth[child] == breadth[node] || breadth[child] > breadth[node])
                    mini = min(mini, breadth[child] + breadth[node] - 1);

                    // parent
                    if(breadth[child] != -1 && breadth[child] < breadth[node])
                    continue;

                    breadth[child] = breadth[node] + 1;
                    q.push(child);
                }

                --size;
            }

            if(mini != 1e9)
            return mini;
        }

        return 1e9;
    }

    int findShortestCycle(int n, vector<vector<int>>& edges) 
    {
        // https://leetcode.com/problems/shortest-cycle-in-a-graph/

        // this has to be O(V * (V + E)) solution, ie, brute force basically.
        // From each node, do BFS. The first time an already visited node is obtained, it is guaranteed
        // to be the smallest cycle for THAT starting node

        // Now, we need to handle even-lengthed and odd-lengthed cycles differently.

        // consider the even-lengthed cycle in example 1
        // start from node 6 and do BFS.
        // let there be breadth array b
        // -> b[6] = 1, 
        // -> b[3] = b[5] = 2
        // now, at node = 3, we will go to 4 and set b[4] = 3
        // then, we go to node = 5 and see that node 4 is already set.
        // However, note that node 4 hasn't been visited in the same breadth. This will be visited in the
        // next breadth.
        // This occurrence will happen only in case of even cycles.
        // For this, our shortest cycle is b[4] + b[5] - 1 (-1 to exclude double counting of starting node)
        // = 4

        // now consider odd-lengthed cycle in eg 1
        // b[0] = 1
        // b[1] = b[2] = 2
        // now, at node = 1, 1 will try to go to 2 and see that it is already visited
        // but here, both have been visited in the same breadth
        // then, formula is still = b[2] + b[1] - 1 = 3

        vector<vector<int>> adj(n);

        for(auto &v: edges)
        {
            adj[v[0]].push_back(v[1]);
            adj[v[1]].push_back(v[0]);
        }

        int curMin = 1e9;
        for(int i=0; i<n; i++)
        curMin = min(curMin, shortestCycle(i, n, adj, curMin));

        return (curMin == 1e9) ? -1 : curMin;
    }
};

int main()
{
    int n = 7;
    vector<vector<int>> edges = {{0,1},{1,2},{2,0},{3,4},{4,5},{5,6},{6,3}};

    Solution ob;
    cout << ob.findShortestCycle(n, edges) << endl;

    return 0;
}