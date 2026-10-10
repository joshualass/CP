#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto check_parity = [&]() -> bool {
        // cout << "check par" << endl;
        int ok = 1;
        auto dfs = [&](auto self, int i, int p, int par) -> void {
            // cout << "i : " << i << " p : " << p << " par : " << par << endl;
            if(sz(adj[i]) == 1) {
                if(par) ok = 0;
            }
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i, par ^ 1);
                }
            }
        };
        for(int i = 0; i < n; i++) {
            if(sz(adj[i]) == 1) {
                dfs(dfs, i, -1, 0);
                return ok;
            }
        }
        assert(0);
    };      

    auto compress = [&]() -> bool {

        vector<vector<int>> nxadj;
        int ok = 1;

        auto dfs = [&](auto self, int i, int p, int par, int nadjp) -> void {
            if(par == 0) {
                int id = sz(nxadj);
                nxadj.push_back({});
                if(nadjp != -1) {
                    nxadj[nadjp].push_back(id);
                    nxadj[id].push_back(nadjp);
                }
                for(int c : adj[i]) {
                    if(c != p) {
                        self(self, c, i, par ^ 1, id);
                    }
                }
            } else {
                if(sz(adj[i]) != 2) {
                    ok = 0;
                    return;
                }
                for(int c : adj[i]) {
                    if(c != p) {
                        self(self, c, i, par ^ 1, nadjp);
                    }
                }
            }
        };
        for(int i = 0; i < n; i++) {
            if(sz(adj[i]) == 1) {
                dfs(dfs, i, -1, 0, -1);
                n = sz(nxadj);
                adj = nxadj;
                return ok;
            }
        }
        assert(0);
    };

    while(1) {
        // cout << "n : " << n << endl;
        // cout << "adj : " << adj << endl;
        if(check_parity() == 0) {
            cout << "NO\n";
            return;
        }
        if(compress() == 0) break;
    }

    cout << "YES\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}