// https://www.youtube.com/watch?v=dOAxrhAUIhA
// https://www.spoj.com/problems/LCASQ/

#include <bits/stdc++.h>
using namespace std;

#define Sort(arr) sort(arr.begin(), arr.end())
#define SortRev(arr) sort(arr.begin(), arr.end(), greater<int>())
#define nl "\n"
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef long long ll;

int up[10000][15];
int depth[10000];

int LOG;

void dfs(int node, vector<vector<int>> &adj)
{
    for(int &child: adj[node])
    {
        depth[child] = depth[node] + 1;
        up[child][0] = node;

        for(int j=1; j<LOG; j++)
        up[child][j] = up[up[child][j - 1]][j - 1];

        dfs(child, adj);
    }
}

int getLCA(int u, int v)
{
    // firstly, get the nodes in the same depth. Only then we can compare
    if(depth[u] < depth[v])
    swap(u, v);

    // make sure that node u has more depth always
    int diff = depth[u] - depth[v];

    // do binary lifting to move up u by diff steps so that both u and v are now
    // in the same depth.
    // this is done so that we get a reference depth from where we can move up
    // both the nodes simulatenously
    for(int i=LOG-1; i>=0; i--)
    {
        if(diff & (1 << i))
        u = up[u][i];
    }

    // LCA is actually v
    if(u == v)
    return v;

    // The idea is this: 
    // We are on the same depth and the nodes are not the same.
    // So we need to move up
    // Start from highest power and move up ONLY IF after moving up, the nodes
    // are not the same.
    // Consider we moved up. Then, we try again with a lower power of 2 and when
    // they are not equal, we move up again.
    // In the end, both the nodes will be the nodes such that, the parent of these
    // nodes is the LCA.

    // Why?
    // Because we never moved up when the jump would have gotten to same node.
    // We moved right when the highest step increase didn't result in same node

    for(int i=LOG-1; i>=0; i--)
    {
        if(up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

void solve()
{
    int n;
    cin >> n;

    LOG = ceil(log2(n));

    // directed tree
    vector<vector<int>> adj(n);
    for(int i=0; i<n; i++)
    {
        int m;
        cin >> m;

        int v;
        for(int j=0; j<m; j++)
        {
            cin >> v;
            adj[i].push_back(v);
        }
    }


    for(int i=0; i<LOG; i++)
    up[0][i] = 0;

    depth[0] = 0;
    dfs(0, adj);

    int q;
    cin >> q;

    while(q > 0)
    {
        int u, v;
        cin >> u >> v;

        cout << getLCA(u, v) << "\n";
        --q;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    ll t = 1;
    // cin >> t;

    while(t--)
    solve();

    return 0;
}