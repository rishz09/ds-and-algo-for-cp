#include<iostream>
#include<vector>

using namespace std;

class DisjointSet
{
    public:
    vector<int> size, parent;
    DisjointSet(int n)
    {
        size.resize(n + 1, 1);
        parent.resize(n + 1);

        for(int i=0; i<=n; i++)
        parent[i] = i;
    }

    int findUPar(int node)
    {
        if(node == parent[node])
        return node;

        return parent[node] = findUPar(parent[node]);
    }

    void unionBySize(int u, int v) 
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        // no need to join them anymore
        if (ulp_u == ulp_v) 
        return;

        if (size[ulp_u] < size[ulp_v]) 
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }

        else 
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

int main()
{
    DisjointSet ds(7);

    ds.unionBySize(1, 2);

    cout << "Size: ";
    for(int i=1; i<=7; i++)
    cout << ds.size[i] << " ";

    cout << endl;
    cout << "Parent: ";
    for(int i=1; i<=7; i++)
    cout << ds.parent[i] << " ";

    cout << endl;
    cout << endl;

    ds.unionBySize(2, 3);

    cout << "Size: ";
    for(int i=1; i<=7; i++)
    cout << ds.size[i] << " ";

    cout << endl;
    cout << "Parent: ";
    for(int i=1; i<=7; i++)
    cout << ds.parent[i] << " ";

    cout << endl;
    cout << endl;

    ds.unionBySize(4, 5);

    cout << "Size: ";
    for(int i=1; i<=7; i++)
    cout << ds.size[i] << " ";

    cout << endl;
    cout << "Parent: ";
    for(int i=1; i<=7; i++)
    cout << ds.parent[i] << " ";

    cout << endl;
    cout << endl;

    ds.unionBySize(6, 7);

    cout << "Size: ";
    for(int i=1; i<=7; i++)
    cout << ds.size[i] << " ";

    cout << endl;
    cout << "Parent: ";
    for(int i=1; i<=7; i++)
    cout << ds.parent[i] << " ";

    cout << endl;
    cout << endl;

    ds.unionBySize(5, 6);

    cout << "Size: ";
    for(int i=1; i<=7; i++)
    cout << ds.size[i] << " ";

    cout << endl;
    cout << "Parent: ";
    for(int i=1; i<=7; i++)
    cout << ds.parent[i] << " ";
    cout << endl;
    cout << endl;
    
    ds.unionBySize(3, 7);

    cout << "Size: ";
    for(int i=1; i<=7; i++)
    cout << ds.size[i] << " ";

    cout << endl;
    cout << "Parent: ";
    for(int i=1; i<=7; i++)
    cout << ds.parent[i] << " ";
    cout << endl;
    
    return 0;
}