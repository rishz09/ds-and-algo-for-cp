#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// found on code360. One test case probably incorrect since it works properly over here
bool res = false;

void findCycle(int node, int par, vector<vector<int>> &adj, vector<bool> &vis, vector<int> &parent,
vector<int> &cycleNodes)
{
    if(res)
    return;

    vis[node] = true;
    parent[node] = par;

    for(int &child: adj[node])
    {
        if(!vis[child])
        {
            findCycle(child, node, adj, vis, parent, cycleNodes);
            if(res)
            return;
        }

        // if visited, but neighbour is not parent, then it means that a cycle has been detected
        else if(child != par)
        {
            int cur = node;
            while(cur != child)
            {
                cycleNodes.push_back(cur);
                cur = parent[cur];
            }

            cycleNodes.push_back(child);
            res = true;
            return;
        }
    }
}

vector<int> smallestPath(int n, vector<vector<int>>edges) 
{
    // firstly, find the nodes which form the cycle.
    vector<vector<int>> adj(n);
    for(auto &vec: edges)
    {
        int a = vec[0];
        int b = vec[1];
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parent(n, -1);
    vector<bool> vis(n, false);
    vector<int> cycleNodes;
    
    findCycle(0, -1, adj, vis, parent, cycleNodes);

    // for(int &ele: cycleNodes)
    // cout << ele << " ";
    // cout << endl;

    // multisource bfs with the cycle nodes at first;
    vector<int> dist(n, 0);
    vis.assign(n, false);

    queue<int> q;
    for(int &ele: cycleNodes)
    {
        q.push(ele);
        vis[ele] = true;
        dist[ele] = 0;
    }

    int d = -1;
    while(!q.empty())
    {
        int size = q.size();
        ++d;
        for(int i=0; i<size; i++)
        {
            int node = q.front();
            q.pop();

            dist[node] = d;

            for(int &child: adj[node])
            {
                if(!vis[child])
                {
                    vis[child] = true;
                    q.push(child);
                }
            }
        }
    }

    return dist;
}

int main()
{
    vector<vector<int>> edges = {{0, 1},
                                {1, 2},
                                {2, 3},
                                {3, 1}};

    int n = 4;
    vector<int> res = smallestPath(n, edges);

    for(int &ele: res)
    cout << ele << " ";
    cout << endl;
}