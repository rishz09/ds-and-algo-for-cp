#include <iostream>
#include <vector>

using namespace std;

// 2D prefix sum over here does this:
// prefix[i][j] = number of 1s present in grid [i..r-1][j..c-1], where, r = number of rows, c = number of columns
// prefix[i][j] = prefix[i][j + 1] + prefix[i + 1][j] - prefix[i + 1][j + 1] + (if prefix[i][j] == 1, then 1, else 0)

// prefix[i + 1][j + 1] is subtracted because it basically subtracts the overlap created by prefix[i][j + 1] and prefix[i + 1][j]

void prefixSum2D(vector<vector<int>> &grid)
{
    int r = grid.size(), c = grid[0].size();

    vector<vector<int>> prefix(r, vector<int> (c));
    prefix[r - 1][c - 1] = (grid[r - 1][c - 1] == 1) ? 1 : 0;

    for(int j=c-2; j>=0; j--)
    prefix[r - 1][j] = prefix[r - 1][j + 1] + ((grid[r - 1][j] == 1) ? 1 : 0);

    for(int i=r-2; i>=0; i--)
    prefix[i][c - 1] = prefix[i + 1][c - 1] + ((grid[i][c - 1] == 1) ? 1 : 0);

    for(int i=r-2; i>=0; i--)
    {
        for(int j=c-2; j>=0; j--)
        prefix[i][j] = prefix[i][j + 1] + prefix[i + 1][j] - prefix[i + 1][j + 1] + ((grid[i][j] == 1) ? 1 : 0);
    }

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        cout << prefix[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> grid = {{1, 1, 0, 1},
                                {1, 0, 1, 0},
                                {1, 0, 1, 1},
                                {0, 0, 0, 1}};

    prefixSum2D(grid);
    return 0;
}