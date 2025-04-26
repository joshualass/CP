#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    
    ll res = 0;

    vector<array<int,3>> vis(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 3; j++) {
            ll sz = 0;

            auto dfs = [&](auto self, int x, int y) -> void {
                if(vis[x][y]) return;
                int at = (s[x] - '0') ^ (y == 1);
                if(at) return;
                vis[x][y] = 1;
                if(y == 0) {
                    sz += x; 
                    if(x) {
                        self(self, x - 1, 0);
                        self(self, x - 1, 1);
                    }
                    if(x != n - 1) {
                        self(self, x + 1, 0);
                    }
                } else if(y == 1) {
                    sz++;
                    if(x) {
                        self(self, x - 1, 2);
                    }
                    if(x != n - 1) {
                        self(self, x + 1, 0);
                    }
                } else {
                    sz += n - x - 1;
                    if(x) {
                        self(self, x - 1, 2);
                    }
                    if(x != n - 1) {
                        self(self, x + 1, 2);
                        self(self, x + 1, 1);
                    }
                }

            };

            dfs(dfs, i, j);

            res = max(res, sz);

        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}