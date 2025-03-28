#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main()
{
    vector<vector<vector<bool>>> vec(5000, vector<vector<bool>> (2, vector<bool> (300)));
    const int maxi = 300;
    vector<pair<bitset<maxi>, bitset<maxi>>> arr(5000);

    bitset<maxi> mask;
    cout << sizeof(mask) * 2 * 5000 << endl;
    cout << sizeof(bool) * (5000 * 2 * 300) << endl;
    return 0; 
}