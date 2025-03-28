// uses powers of 2 to get kth ancestor of a node in tree
#include <bits/stdc++.h>

using namespace std;

// adj is directed, and we assume that tree is rooted at 0
vector<vector<int>> up, adj;
vector<int> depth;
int LOG;

void dfs(int);

void initialize(int n, vector<int>& parent) 
{
    LOG = ceil(log2(n));
    up = vector<vector<int>> (n, vector<int> (LOG));
    adj = vector<vector<int>> (n);   // directed tree
    depth = vector<int> (n);
    
    for(int i=1; i<n; i++)
    {
        int par = parent[i];
        adj[par].push_back(i);
    }
    
    // sort of a limiter to stay stuck at 0th node if k > distance between queried node and root
    parent[0] = 0;    
    
    for(int i=0; i<LOG; i++)
    up[0][i] = 0;
    
    depth[0] = 0;
    dfs(0);
}
        
// generalised DFS
// We can run a loop from node = 0 to n and then loop over LOG IFF for every node, its parent value
// is less than node value. But for general case, do DFS
    
void dfs(int node)
{
    for(int &child: adj[node])
    {
        depth[child] = depth[node] + 1;
    
        up[child][0] = node;
        for(int j=1; j<LOG; j++)
        up[child][j] = up[up[child][j - 1]][j - 1];
    
        dfs(child);
    }
}
    
int getKthAncestor(int node, int k) 
{
    // the stuck at 0 thing works perfectly, but it has been explicitly mentioned over here that if
    // k exceeds distance from root, simply return -1 so we will keep track of depth
    if(k > depth[node])
    return -1;
    
    for(int j=0; j<LOG; j++)
    {
        // moving in powers of 2
        if(k & (1 << j))
        node = up[node][j];
    }    
    
    return node;
}


int main()
{
    int n = 7;
    vector<int> parent = {-1,0,0,1,1,2,2};

    initialize(7, parent);

    cout << getKthAncestor(3, 1) << endl;
    cout << getKthAncestor(5, 2) << endl;
    cout << getKthAncestor(6, 3) << endl;

    return 0;
}