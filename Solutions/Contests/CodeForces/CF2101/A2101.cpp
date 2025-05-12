#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4]{-1, 0, 1, 0}, dy[4]{0, 1, 0, -1};

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));

    if(n & 1) {
        int p = 1;
        int x = n / 2 + 1, y = n / 2 - 1;
        for(int i = 2; i < n; i += 2) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < i; k++) {
                    x += dx[j], y += dy[j];
                    // cout << "x : " << x << " y : " << y << endl;
                    a[x][y] = p++;
                }
            }
            y--;
            x++;
        }
    } else {
        int p = 4;
        a[n/2-1][n/2] = 1;
        a[n/2][n/2] = 2;
        a[n/2][n/2-1] = 3;
        int x = n / 2 + 1, y = n / 2 - 2;
        for(int i = 3; i < n; i += 2) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < i; k++) {
                    x += dx[j], y += dy[j];
                    a[x][y] = p++;
                }
            }
            y--;
            x++;
        }
    }

    for(auto x : a) {
        for(auto y : x) cout << y << " ";
        cout << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}