#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

vector<vi> treeJump(vi& P) {
    // cout << "zz0" << endl;
    int on = 1, d = 1;
    while(on < sz(P)) on *= 2, d++;
    // cout << "zz1" << endl;
    vector<vi> jmp(d, P);
    // cout << "zz2" << endl;
    // cout << "d : " << d << endl;
    rep(i, 1, d) rep(j, 0, sz(P)) {
        // cout << "i : " << i << " j : " << j << endl;
        jmp[i][j] = jmp[i-1][jmp[i-1][j]];
    }
    // cout << "zz3" << endl;
    return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps) {
    rep(i, 0, sz(tbl))
        if(steps & (1 << i)) nod = tbl[i][nod];
    return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    a = jmp(tbl, a, depth[a] - depth[b]);
    if(a == b) return a;
    for(int i = sz(tbl); i--;) {
        int c = tbl[i][a], d = tbl[i][b];
        if(c != d) a = c, b = d;
    }
    return tbl[0][a];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, q; cin >> n >> q;

    vector<vector<int>> adj(n);
    for(int i = 0; i < n + 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // cout << "ok0 " << endl;

    vector<int> p(n), vis(n), depths(n);
    vector<array<int,2>> ex;

    auto dfs = [&](auto self, int i, int par, int d) -> void {
        p[i] = par;
        depths[i] = d;
        vis[i] = 1;

        for(int c : adj[i]) {
            if(c != par) {
                if(vis[c]) {
                    if(i < c) ex.push_back({i, c});
                } else {
                    self(self, c, i, d + 1);
                }
            }
        }
    };

    dfs(dfs, 0, 0, 0);

    // cout << "ok1 " << endl;
    // cout << "p" << endl;
    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " p[i] : " << p[i] << endl;
    // }

    // cout << "ex" << endl;
    // for(auto x : ex) cout << x[0] << ", " << x[1] << endl;

    // cout << "jump sucks" << endl;
    auto tbl = treeJump(p);
    // cout << "ok2 " << endl;

    assert(ex.size() == 2);
    // cout << "ok3 " << endl;

    vector<vector<array<int,2>>> cart;
    for(int i = 0; i < ex.size(); i++) {
        cart.push_back(vector<array<int,2>>());
        cart.back().push_back(ex[i]);
        swap(ex[i][0],ex[i][1]);
        cart.back().push_back(ex[i]);
    }
    cart.push_back(vector<array<int,2>>());
    cart.back().push_back({-1,-1});

    auto intersect = [&](array<int,2> a, array<int,2> b) -> bool {
        auto check = [&](int u, int lcu, int v, int lcv) -> bool {
            // if(u == lcu || v == lcv) return 0;
            int lo_depth_lca = max(depths[lcu], depths[lcv]);
            return jmp(tbl, u, depths[u] - lo_depth_lca) == jmp(tbl, v, depths[v] - lo_depth_lca);
        };
        int alc = lca(tbl, depths, a[0], a[1]), blc = lca(tbl, depths, b[0], b[1]);
        for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) if(check(a[i], alc, b[j], blc)) return 1;
        return 0;
    };

    for(int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        int res = 0;
        for(int j = 0; j < cart.size(); j++) {
            for(int k = 0; k < cart.size() - 1; k++) {
                if(j != k) {
                    for(int l = 0; l < cart[j].size(); l++) {
                        for(int m = 0; m < cart[k].size(); m++) {
                            vector<array<int,2>> path;
                            int prev = u;
                            if(cart[j][l][0] != -1) {
                                path.push_back({prev, cart[j][l][0]});
                                prev = cart[j][l][1];
                            }

                            if(cart[k][m][0] != -1) {
                                path.push_back({prev, cart[k][m][0]});
                                prev = cart[k][m][1];
                            }

                            path.push_back({prev, v});

                            int ok = 1;
                            for(int o = 0; o < path.size(); o++) {
                                for(int k = o + 1; k < path.size(); k++) {
                                    if(intersect(path[o],path[k])) ok = 0;
                                }
                            }
                            if(ok) {
                                // cout << "testing\n";
                                // cout << "use edge : " << cart[j][l][0] << ", " << cart[j][l][1] << '\n';
                                // cout << "use edge : " << cart[k][m][0] << ", " << cart[k][m][1] << '\n';
                                // cout << "path\n";
                                // for(auto x : path) cout << x[0] << ", " << x[1] << endl;
                                // cout << '\n';
                                // cout << "ok ? " << ok << '\n';
                            }
                            res += ok;
                        }
                    }
                }
            }
        }
        cout << res + 1 << '\n';
    }

    return 0;
}

/*
4 1
1 2
1 3
1 4
2 3
2 4
1 3

*/