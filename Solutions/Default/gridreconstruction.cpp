#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) {
        int n; cin >> n;
        vector<vector<int>> grid(2,vector<int>(n,-1));
        int counter = 1;
        for(int i = 0; i < n; i++) {
            grid[(i+1)%2][i] = i + 1;
            counter++;
        }
        grid[0][0] = n*2;
        grid[1][n-1] = n*2 - 1;
        for(int i = 1; i < n - 1; i++) {
            grid[i % 2][i] = counter++;
        }
        string out = to_string(grid[0][0]);
        string out2 = to_string(grid[1][0]);
        for(int i = 1; i < n; i++) {
            out += " " + to_string(grid[0][i]);
            out2 += " " + to_string(grid[1][i]);
        }
        cout << out << "\n" << out2 << "\n";
    }

    return 0;
}