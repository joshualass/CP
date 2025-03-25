#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int lifts[20][200000];


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<map<int,int>> ss(n);
    vector<int> d(n);

    auto dfs0 = [&](auto self, int i, int p, int depth) -> int {
        int cnt = 1;
        lifts[0][i] = p;
        d[i] = depth;
        for(int x : adj[i]) {
            if(x != p) {
                int t = self(self, x, i, depth + 1);
                ss[i][x] = t;
                cnt += t;
            }
        }
        if(p != -1) {
            ss[i][p] = n - cnt;
        }
        return cnt;
    };

    dfs0(dfs0, 0, -1, 0);

    auto get_lift = [&](int i, int l) -> int {
        if(i == -1) return -1;
        return lifts[l][i];
    };

    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            lifts[i][j] = get_lift(get_lift(j, i - 1), i - 1);
        }
    }

    auto get_dist = [&](int i, int j) -> int {
        if(d[i] < d[j]) swap(i,j);
        int res = d[i] - d[j];
        for(int k = 0; k < 20; k++) {
            if((res >> k) & 1) {
                i = get_lift(i, k);
            }
        }

        if(i == j) {
            return res;
        }
        for(int k = 19; k >= 0; k--) {
            if(get_lift(i, k) != get_lift(j, k)) {
                res += 1 << (k + 1);
                i = get_lift(i, k);
                j = get_lift(j, k);
            }
        }

        return res + 2;

    };

    //gets first node on i's path to node j
    auto get_node_in_dir = [&](int i, int j) -> int {

        if(get_dist(i, j) == abs(d[i] - d[j])) {
            if(d[i] > d[j]) {
                return get_lift(i, 0);
            }
            int res = d[j] - d[i] - 1;
            for(int k = 19; k >= 0; k--) {
                if((res >> k) & 1) {
                    j = get_lift(j, k);
                }
            }
            return j;
        }
        return get_lift(i, 0);
    };

    for(int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        u--; v--;

        int udir = get_node_in_dir(u, v);
        int vdir = get_node_in_dir(v, u);
        int uss = n - ss[u][udir] - 1;
        int vss = n - ss[v][vdir] - 1;

        ll res = uss + vss;

        ll nodes_on_path = get_dist(u, v) + 1;
        res += nodes_on_path * (nodes_on_path + 1) / 2;
        ll left = n - nodes_on_path - uss - vss;
        res += left;
        
        cout << res << '\n';

    }


    return 0;
}
