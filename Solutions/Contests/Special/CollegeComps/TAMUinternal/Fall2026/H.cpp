#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()
const ll D = 20;

//fills vector<vector<T>> jumps with the binary jumps. 
template<typename T>
void buildJumps(vector<T> &edges, vector<vector<T>> &jumps, ll depth = 64) {
    jumps.assign(edges.size(), vector<T>(depth));
    for(ll i = 0; i < depth; i++) {
        for(ll j = 0; j < edges.size(); j++) {
            if(i == 0) jumps[j][i] = (edges[j] == -1 ? j : edges[j]);
            else jumps[j][i] = jumps[jumps[j][i-1]][i-1];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    vector<vector<ll>> adj(n);
    for(ll i = 1; i < n; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<ll>> jumps(n, vector<ll>(D));
    vector<ll> depths(n);
    auto dfs = [&](auto self, ll i, ll p, ll dep) -> void {
        jumps[i][0] = p;
        depths[i] = dep;
        for(ll c : adj[i]) {
            if(c != p) {
                self(self, c, i, dep + 1);
            }
        }
    };

    dfs(dfs, 0, 0, 0);

    for(ll i = 1; i < D; i++) {
        for(ll j = 0; j < n; j++) {
            jumps[j][i] = jumps[jumps[j][i-1]][i-1];
        }
    }

    vector<array<ll,3>> z(m);
    for(auto &x : z) {
        for(auto &y : x) {
            cin >> y;
        }
        x[1]--;
        x[2]--;
    }

    auto jump = [&](ll x, ll dis) -> ll {
        for(ll i = D - 1; i >= 0; i--) {
            if((dis >> i) & 1) {
                x = jumps[x][i];
            }
        }
        return x;
    };

    auto get_lca = [&](ll a, ll b) -> ll {
        if(depths[a] > depths[b]) {
            swap(a, b);
        }
        b = jump(b, depths[b] - depths[a]);
        for(ll i = D - 1; i >= 0; i--) {
            if(jumps[a][i] != jumps[b][i]) {
                a = jumps[a][i];
                b = jumps[b][i];
            }
        }
        if(a == b) return a;
        return jumps[a][0];
    };

    auto get = [&](ll time) -> ll {

        // cout << "time : " << time << endl;
        vector<ll> d(n);

        for(auto [t, a, b] : z) {
            ll lca = get_lca(a, b);
            if(time >= t) {
                ll first_path = depths[a] - depths[lca] + 1;
                ll second_path = depths[b] - depths[lca];

                ll path_time = min(first_path + second_path, time - t + 1);

                ll first_len = min(path_time, first_path);
                path_time -= first_len;
                ll second_len = path_time;

                d[a]++;
                ll stop = jump(a, first_len - 1);
                if(stop) {
                    d[jumps[stop][0]]--;
                }

                ll start = jump(b, depths[b] - depths[lca] - second_len);
                d[start]++;
                d[lca]--;
            }
        }

        ll res = 0;
        auto dfs = [&](auto self, ll i, ll p) -> ll {
            ll cur = d[i];
            for(ll c : adj[i]) {
                if(c != p) {
                    cur += self(self, c, i);
                }
            }
            res = max(res, cur);
            return cur;
        };

        dfs(dfs, 0, 0);
        // cout << "res : " << res << endl;
        return res;
    };

    ll Y = get(2e9);
    ll l = 0, r = 2e9;
    while(l != r) {
        ll m = (l + r) / 2;
        // cout << "l : " << l << " r : " << r << " m : " << m << endl;
        if(get(m) == Y) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    
    cout << l << '\n';

    return 0;
}
