#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int m, r, d; cin >> m >> r >> d;
    m--; r--; d--;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ld res;

    auto dfs = [&](auto self, int i, int p) -> array<int,2> {
        // cout << "i : " << i << endl;
        vector<array<int,2>> ch;
        for(int c : adj[i]) {
            if(c != p) {
                auto t = self(self, c, i);
                if(t[0] != -1) ch.push_back(t);
            }
        }
        if(sz(ch) == 2) {
            sort(ch.begin(), ch.end());
            int num = ch[1][1];
            int den = ch[0][1] + ch[1][1];
            res = ((ld) num) / ((ld) den);
            return {-1, -1};
        } else if(sz(ch) == 1) {
            if(i == r) {
                res = 1;
                return {-1, -1};
            } else if(i == d) {
                res = 0;
                return {-1, -1};
            } else {
                ch[0][1]++;
                return ch[0];
            }
        } else {
            if(i == r) return {0, 1};
            if(i == d) return {1, 1};
            return {-1, -1};
        }
        cout << "no return? " << endl;
    };

    dfs(dfs, m, -1);

    cout << fixed << setprecision(15) << res << '\n';

    return 0;
}
