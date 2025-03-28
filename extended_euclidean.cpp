#include <iostream>
#include <math.h>

using namespace std;

// finds GCD of a and b, and finds coefficient to represent gcd in linear combination of a and b
// gcd = ax + by

int extended_euclidean(int a, int b, int &x, int &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = extended_euclidean(b, a % b, x1, y1);

    x = y1;
    y = x1 - (y1 * floor(a / b));  // equivalent to just a / b in int terms

    return g;
}

int main()
{
    int a = 2, b = 1e9 + 7;
    int x, y;

    int g = extended_euclidean(a, b, x, y);
    cout << "GCD: " << g << endl;
    cout << "x: " << x << "\ty: " << y << endl;

    return 0;
}