#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// note, this algorithm only works if it is guaranteed that eulerian path / cycle exists
// hierholzer algo finds the eulerian path / cycle, starting at a given node

void hierholzer(int node, vector<vector<int>> &adj, vector<int> &path)
{
    while(adj[node].size() != 0)
    {
        int neighbor = adj[node].back();
        adj[node].pop_back();
        hierholzer(neighbor, adj, path);
    }

    path.push_back(node);
}

int main()
{
    // considering a directed graph in this case. But can be done with undirected graph as well
    vector<vector<int>> edges = {{0, 1},
                                 {1, 2},
                                 {2, 3},
                                 {3, 4},
                                 {4, 2}};

    vector<vector<int>> adj(5);

    int size = edges.size();
    for(int i=0; i<size; i++)
    {
        int a = edges[i][0];
        int b = edges[i][1];
        adj[a].push_back(b);
    }

    vector<int> path;
    hierholzer(0, adj, path);

    // path is given in reverse
    reverse(path.begin(), path.end());
    for(int ele: path)
    cout << ele << " ";
    cout << endl;
}