/*
https://youtu.be/CsGP_s_3GWg?si=hp-6Q4i7nXuoyfiL
https://youtu.be/qrAub5z8FeA?si=2_cASPMp6n1IX3Tf
https://cp-algorithms.com/graph/bridge-searching.html

Bridges in a graph are edges, which on removal, make the graph disconnected.
The idea is to use DFS

We keep 2 arrays: tin[] and low[]
-> tin[node] stores the time at which a node enters DFS
-> low[node] stores the lowest tin of any of its neighboring node, except the parent from which it came from

The idea is this:
Let us be at a node.
-> The edge {node, child} is a bridge if low[child] > tin[node].

Why?
If low[child] <= tin[node], it would have meant that the child could be reached from some other node which was reached BEFORE the current node.
Consider a cyclic graph of nodes A B C
A - B, B - C, C - A

(initially, all low[i] = tin[i])
We do DFS from A -> B -> C
tin[A] = 0, tin[B] = 1, tin[C] = 2
low[C] = 0, low[B] = 0, low[A] = 0

See that when we are at C, we can go back to A, but A is already visited and A is C's neighbour. So low[C] = low[A] = 0
Then, C is B's neighbour, so low[B] = low[C] = 0

When B is out of its DFS, control will go to B and B asks if B - C edge is a bridge or not
Now, tin[B] = 1, low[C] = 0
low[child] > tin[node] is therefore not true. So, B - C edge is not a bridge

low[C] = 0 basically tells us that, if we remove the edge B - C, where tin[B] = 1, C can still be reached from a node which had lower tin than B.
So like, there is a possible DFS route such that we will reach C before even reaching B.
Therefore, B - C is not a bridge

Quite simple intuition
*/

#include <iostream>
#include <vector>

using namespace std;

int t;
void dfs(int node, int parent, vector<vector<int>> &adj, vector<int> &tin, vector<int> &low, vector<bool> &vis, vector<vector<int>> &res)
{
    vis[node] = true;
    tin[node] = low[node] = t;
    ++t;

    for(int &child: adj[node])
    {
        if(child == parent)
        continue;

        if(!vis[child])
        {
            dfs(child, node, adj, tin, low, vis, res);
            low[node] = min(low[node], low[child]);

            if(low[child] > tin[node])
            res.push_back({node, child});
        }

        else
        {
            // if child is already visited, then it has been visited in the same dfs tree at earlier stage, so definitely no need for bridge checking 
            // because even if we remove this edge, its parent will be connected to the child since it came from there
            // so just update low
            low[node] = min(low[node], low[child]);
        }
    }
}

void bridges_in_graph(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> adj(n);
    for(auto &v: edges)
    {
        adj[v[0]].push_back(v[1]);
        adj[v[1]].push_back(v[0]);
    }

    vector<int> tin(n), low(n);
    vector<bool> vis(n, false);

    t = 0;
    
    vector<vector<int>> res;

    // single dfs call, assuming the whole graph is connected
    dfs(0, -1, adj, tin, low, vis, res);

    for(auto &v: res)
    cout << v[0] << " " << v[1] << "\n";
}

int main()
{
    // striver's example
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {0, 3}, {3, 4}, {4, 5},
                                 {5, 6}, {5, 8}, {6, 7}, {7, 8}, {7, 9}, {9, 11},
                                 {9, 10}, {10, 11}};

    bridges_in_graph(12, edges);
    return 0;
}