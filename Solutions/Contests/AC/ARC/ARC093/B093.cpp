#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b; cin >> a >> b;
    vector<string> grid;
    for(int i = 0; i < 50; i++) {
        grid.push_back(string(100, '.'));
    }
    for(int i = 0; i < 50; i++) {
        grid.push_back(string(100,'#'));
    }

    a--; b--;

    for(int i = 0; i < 100; i += 2) {
        for(int j = 0; j < 100; j += 2) {
            if(b) {
                grid[i][j] = '#';
                b--;
            }
        }
    }

    for(int i = 51; i < 100; i += 2) {
        for(int j = 0; j < 100; j += 2) {
            if(a) {
                grid[i][j] = '.';
                a--;
            }
        }
    }

    cout << "100 100\n";
    for(auto x : grid) {
        cout << x << '\n';
    }

    return 0;
}