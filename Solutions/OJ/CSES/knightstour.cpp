#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//cyclic solution :)
vector<vector<int>> soln = {
    {26, 37, 6, 49, 28, 35, 8, 59}, 
    {5, 50, 27, 36, 7, 60, 17, 34}, 
    {38, 25, 62, 15, 48, 29, 58, 9},
    {51, 4, 47, 30, 61, 16, 33, 18},
    {24, 39, 14, 63, 32, 45, 10, 57},
    {3, 52, 31, 46, 13, 64, 19, 44},
    {40, 23, 54, 1, 42, 21, 56, 11},
    {53, 2, 41, 22, 55, 12, 43, 20}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, y; cin >> y >> x;
    x--; y--;
    int sub = (soln[x][y] - 1);
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            cout << (64 + soln[i][j] - sub - 1) % 64 + 1 << " \n"[j == 7];
        }
    }    

    return 0;
}
