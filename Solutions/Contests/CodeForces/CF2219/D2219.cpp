#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
void buildJumps(vector<T> &edges, vector<vector<T>> &jumps, int depth = 64) {
    jumps.assign(edges.size(), vector<T>(depth));
    for(int i = 0; i < depth; i++) {
        for(int j = 0; j < edges.size(); j++) {
            if(i == 0) jumps[j][i] = (edges[j] == -1 ? j : edges[j]);
            else jumps[j][i] = jumps[jumps[j][i-1]][i-1];
        }
    }
}

void solve() {
    
    int n; cin >> n;
    vector<int> p(n), ip(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        ip[p[i]] = i;
    }

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> par(n), dep(n), ss(n);

    auto dfs = [&](auto self, int i, int p, int d) -> int {
        par[i] = p;
        dep[i] = d;
        int res = 1;
        for(int c : adj[i]) {
            if(c != p) {
                res += self(self, c, i, d + 1);
            }
        }
        ss[i] = res;
        return res;
    };

    dfs(dfs, 0, -1, 0);

    vector<vector<int>> lifts;
    buildJumps(par, lifts, 20);

    auto jump = [&](int idx, int jumps) -> int {
        for(int i = 19; i >= 0; i--) {
            if((jumps >> i) & 1) {
                idx = lifts[idx][i];
            }
        }
        return idx;
    };

    vector<ll> contribs(n + 1);
    vector<ll> mex_idx(n);
    vector<int> mex_here(n);

    int lo = -1;

    for(int i = 0; i < n; i++) {
        int idx = ip[i];
        if(i == 0) {
            lo = idx;
        } else {
            if(lo != -1) {
                int lo_dep = dep[lo], idx_dep = dep[idx];
                if(lo_dep < idx_dep) {
                    int t = jump(idx, idx_dep - lo_dep);
                    if(t == lo) {
                        lo = idx;
                    } else {
                        lo = -1;
                    }
                } else {
                    int t = jump(lo, lo_dep - idx_dep);
                    if(t != idx) {
                        lo = -1;
                    }
                }
            }
        }

        mex_idx[i] = lo;

        if(lo != -1) {
            contribs[i] += ss[lo];
            mex_here[lo] = i + 1;
        }
    }

    auto dfs2 = [&](auto self, int i, int p, int mex) -> void {
        mex = max(mex, mex_here[i]);
        mex_here[i] = mex;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, mex);
            }
        }
    };

    dfs2(dfs2, 0, -1, 0);

    for(int i = n - 1; i >= 0; i--) contribs[i] += contribs[i+1];
    ll res = contribs[0];

    for(int i = 0; i < n; i++) {
        ll here = res;
        here -= contribs[p[i] + 1];

        int fv = mex_here[i];
        

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