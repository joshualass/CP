#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
C. Cable Pruning
*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<vector<array<ll,2>>> adj(n);
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        sum += w;
    }

    int start = -1, vis_start = 0;
    vector<int> vis(n), cycle;
    auto dfs = [&](auto self, int i, int p) -> void {
        vis[i] = 1;
        for(auto [c, w] : adj[i]) {
            if(c != p && start == -1) {
                if(vis[c]) {
                    start = c;
                } else {
                    self(self, c, i);
                }
            }
        }
        if(start != -1 && vis_start == 0) cycle.push_back(i);
        if(i == start) vis_start = 1;
    };
    dfs(dfs, 0, -1);

    // cout << "cycle : " << cycle << endl;

    vector<int> tree_id(n), d(n);
    vector<vector<int>> lifts(n, vector<int>(20));
    auto dfstree = [&](auto self, int i, int p, int id, int depth) -> void {
        tree_id[i] = id;
        lifts[i][0] = p;
        d[i] = depth;
        // cout << "i : " << i << " p : " << p << " id : " << id << " depth : " << depth << endl;
        for(auto [c, w] : adj[i]) {
            if(c != p) {
                self(self, c, i, id, depth + 1);
            }
        }
    };

    int cs = sz(cycle);

    for(int i = 0; i < cs; i++) {
        lifts[cycle[i]][0] = cycle[i];
        tree_id[cycle[i]] = i;
        int nx = cycle[(i + 1) % cs], prev = cycle[(i + cs - 1) % cs];
        for(auto [c, w] : adj[cycle[i]]) {
            if(c != nx && c != prev) {
                // cout << "call dfs c : " << c << " cycle[i] : " << cycle[i] << endl;
                dfstree(dfstree, c, cycle[i], i, 1);
            }
        }
    }

    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            lifts[j][i] = lifts[lifts[j][i-1]][i-1];
        }
    }

    vector<int> ups(n);
    vector<ll> hashes(n);

    //returns depth of lca
    auto lca = [&](int a, int b) -> int {
        if(d[a] < d[b]) swap(a,b);
        int diff = d[a] - d[b];
        for(int i = 19; i >= 0; i--) {
            if((diff >> i) & 1) {
                a = lifts[a][i];
            }
        }
        if(a == b) return d[a];
        for(int i = 19; i >= 0; i--) {
            if(lifts[a][i] != lifts[b][i]) {
                a = lifts[a][i];
                b = lifts[b][i];
            }
        }
        return d[a] - 1;
    };

    // cout << "d : " << d << endl;

    for(int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if(tree_id[a] == tree_id[b]) {
            int lca_depth = lca(a, b);
            ups[a] = max(ups[a], d[a] - lca_depth);
            ups[b] = max(ups[b], d[b] - lca_depth);
        } else {
            ups[a] = d[a];
            ups[b] = d[b];
            a = tree_id[a];
            b = tree_id[b];
            ll hash = rng();
            hashes[a] ^= hash;
            hashes[b] ^= hash;
        }
    }

    ll res = 0;

    // cout << "init ups : " << ups << endl;

    auto solve_tree = [&](auto self, int i, int p, ll ew) -> void {
        // cout << "i : " << i << " p : " << p << " ew : " << ew << endl;
        for(auto [c, w] : adj[i]) {
            if(c != p) {
                self(self, c, i, w);
                ups[i] = max(ups[i], ups[c] - 1);
            }
        }
        // cout << "done i : " << i << " ups : " << ups[i] << endl;
        if(ups[i] == 0) {
            res += ew;
        }
    };

    ll curr_hash = 0;
    map<ll,ll> m;

    for(int i = 0; i < cs; i++) {
        curr_hash ^= hashes[i];
        //solve the subtrees
        int nx = cycle[(i + 1) % cs], prev = cycle[(i + cs - 1) % cs];
        for(auto [c, w] : adj[cycle[i]]) {
            if(c != nx && c != prev) {
                solve_tree(solve_tree, c, cycle[i], w);
                // cout << "call dfs c : " << c << " cycle[i] : " << cycle[i] << endl;
                dfstree(dfstree, c, cycle[i], i, 1);
            }
            if(c == cycle[(i+1) % cs]) {
                m[curr_hash] += w;
            }
        }
    }

    ll mx = 0;
    for(auto [k, v] : m) {
        mx = max(mx, v);
    }

    // cout << "sum : " << sum << " mx : " << mx << " trees : " << res << endl;

    cout << sum - mx - res << '\n';

    return 0;
}
