#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;

    vector<vector<int>> adj(n);

    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> cnts(n);

    auto dfs0 = [&](auto self, int i, int p) -> void {
        vector<int> ch;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                ch.push_back(cnts[c]);
            }
        }
        if(sz(ch) % 2 == 0) {
            cnts[i] = 1;
        } else {
            cnts[i] = accumulate(ch.begin(), ch.end(), 0);
        }
    };

    ll res = 0;

    auto dfs1 = [&](auto self, int i, int p) -> void {
        vector<int> ch;
        for(int c : adj[i]) {
            if(c != p) {
                ch.push_back(cnts[c]);
            }
        }
        if(p != -1) {
            ch.push_back(cnts[p]);
        }
        int sum = accumulate(ch.begin(), ch.end(), 0);
        if(sz(ch) % 2 == 1) {
            res += sum;
        }
        for(int c : adj[i]) {
            if(c != p) {
                if(sz(ch) % 2 == 0) {
                    cnts[i] = sum - cnts[c];
                } else {
                    cnts[i] = 1;
                }
                self(self, c, i);
            }
        }
    };

    dfs0(dfs0, 0, -1);
    dfs1(dfs1, 0, -1);

    cout << res / 2 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}