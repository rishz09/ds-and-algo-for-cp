/*
https://www.youtube.com/watch?v=R6uoSjZ2imo&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=54&t=1165s
https://cp-algorithms.com/graph/strongly-connected-components.html

Kosaraju's Algorithm is used to find Strongly Connected Components (SCCs) in directed graph

SCC is a subgraph such that for any node a and b in the subgraph, a is reachable from b and vice versa.

A condensed graph after finding out SCCs looks like this:

SCC1 -> SCC2 -> SCC3 -> SCC4

SCCs are only one way reachable. If SCC1 was reachable from SCC2 as well, then they could have been condensed to form a larger SCC. Hence, a condensed graph always looks like this

Notice that for any node in SCC1, if we start DFS from it, we can cover the whole graph.
Our solution building will start from here

-> Consider we have reversed all the edges of the graph
-> Then, graph is: SCC1 <- SCC2 <- SCC3 <- SCC4

Now notice this:
Since within each SCC, every node was traversable, so even after reversing edges, every node inside an SCC still remains traversible.

But now, if we start with a node from SCC1 and do DFS, we will ONLY cover nodes of SCC1.

Then we do DFS in a node from SCC2. It will traverse only SCC2 nodes (not SCC1 nodes because they have been visited already)

So, now we need an order of nodes such that we start DFS from SCC1 nodes first, then go to SCC2 and so on. This is required because suppose, if we start with SCC4 node,
then we will traverse the whole graph and won't be able to find SCCs.

How to arrange nodes:
-> We will do DFS in original graph and arrange the nodes in descending order of exit time.
-> This means that, we start DFS with node n and DFS goes to its children. Now, when all children of n will have been traversed, it will be time for node n to exit from
-> its recursive function. This is the exit time.
-> It can be noticed that if we arrange the nodes this way, nodes of SCC1 will always remain at the top. Then SCC2, then SCC3 and so on.
-> Take Striver's graph example from the video and try it out.

Now we have arranged nodes.
We now do DFS on reversed graph.

-> Start with the node with highest exit time. Obviously, this will be present in SCC1.
-> In the reversed graph, if we start from SCC1, we will cover all nodes of SCC1 but won't cover any other node.
-> So, in the DFS call, whichever nodes are traversed, forms a Strongly Connected Component.
-> Next, if we pick up another node from SCC1, do not do DFS because it is already visited from the previous node.
-> Start DFS again from a node which hasn't been visited. This will be a node from SCC2, then SCC3 and so on.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs1(int node, vector<bool> &vis, vector<vector<int>> &adj, stack<int> &st)
{
    vis[node] = true;

    for(int &child: adj[node])
    {
        if(!vis[child])
        dfs1(child, vis, adj, st);
    }
    
    st.push(node);
}

void dfs2(int node, vector<bool> &vis, vector<vector<int>> &adjRev, vector<int> &temp)
{
    vis[node] = true;
    temp.push_back(node);

    for(int &child: adjRev[node])
    {
        if(!vis[child])
        dfs2(child, vis, adjRev, temp);
    }
}

void kosaraju(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> adj(n);
    for(auto &v: edges)
    adj[v[0]].push_back(v[1]);

    stack<int> st;
    vector<bool> vis(n, false);

    for(int i=0; i<n; i++)
    {
        if(!vis[i])
        dfs1(i, vis, adj, st);
    }


    vector<vector<int>> adjRev(n);
    for(auto &v: edges)
    {
        vis[v[0]] = false;
        vis[v[1]] = false;

        adjRev[v[1]].push_back(v[0]);
    }

    
    vector<vector<int>> res;
    int SCC = 0;

    while(!st.empty())
    {
        int node = st.top();
        st.pop();

        if(!vis[node])
        {
            // whenever a dfs is called, it starts a new SCC
            ++SCC;
            vector<int> temp;
            dfs2(node, vis, adjRev, temp);

            res.push_back(temp);
        }
    }

    cout << "Number of SCCs: " << SCC << endl;

    cout << "\nComponents: " << endl;
    for(auto &v: res)
    {
        for(int &ele: v)
        cout << ele << " ";
        cout << "\n";
    }
}

int main()
{
    // vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4},
    //                              {4, 5}, {5, 6}, {6, 4}, {6, 7}, {4, 7}};

    int n = 4;
    vector<vector<int>> edges = {{0,1},{1,0},{1,2},{3,2}};

    kosaraju(n, edges);
    return 0;
}