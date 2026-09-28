#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    vector<int> vis(1 << n);
    vis[0] = 1;
    for(int i = 0; i < 1 << n; i++) {
        if(vis[i]) {
            for(int j = 0; j < n; j++) {
                if(((i >> j) & 1) == 0) {
                    int nxbm = i + (1 << j);
                    if(s[nxbm - 1] == '0') {
                        vis[nxbm] = 1;
                    }
                }
            }
        }
    }

    cout << (vis[(1 << n) - 1] ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}