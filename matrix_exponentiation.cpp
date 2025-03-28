// tool to speed up DP with constant space
// useful when current DP state is dependent on only previous state or a fixed number of previous states

// when current state is dependent on variable number of previous states (eg: from dp[1] to dp[n - 1]),
// matrix exponentiation not preferred

// Note that over here, matrix size is 2 x 2 but obviously this can be generalized
// How does matrix exponentation help in solving problems?
// Solve Errichto's sheet to understand
#include <iostream>
#include <vector>

using namespace std;

struct Matrix
{
    double a[2][2] = {{0, 0}, {0, 0}};

    Matrix operator *(const Matrix &other)
    {
        Matrix product;
        // matrix multiplication is kind of like floyd warshall
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<2; j++)
            {
                for(int k=0; k<2; k++)
                product.a[i][k] += a[i][j] * other.a[j][k];
            }
        }

        return product;
    }
};

Matrix expo_power(Matrix a, int k)
{
    // need A^k in O(N^3 log k) time, N = number of rows or columns in matrix
    Matrix res;
    for(int i=0; i<2; i++)
    res.a[i][i] = 1;
    
    // making initial matrix to be an identity matrix, similar to res = 1 in binary
    // exponentiation

    while(k > 0)
    {
        if(k % 2 == 1)
        res = res * a;

        a = a * a;
        k /= 2;
    }

    return res;
}

int main()
{
    Matrix a;
    a.a[0][0] = 2;
    a.a[0][1] = 3;
    a.a[1][0] = 1;
    a.a[1][1] = 5;

    int k = 5;

    Matrix res = expo_power(a, k);
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        cout << res.a[i][j] << " ";
        cout << endl;
    }

    return 0;
}