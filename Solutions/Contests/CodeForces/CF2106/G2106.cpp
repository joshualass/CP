#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto ask = [&](int type, vector<int> nodes) -> int {
        cout << "? " << type + 1 << " ";
        if(type == 0) {
            cout << nodes.size();
            for(int x : nodes) cout << " " << x + 1;
        } else {
            cout << nodes[0] + 1;
        }
        cout << endl;
        if(type == 0) {
            int res; cin >> res;
            return res;
        }
        return -1;
    };

    auto get_diff = [&](int t, vector<int> c, int l, int r) -> int {
        c = vector<int>(c.begin() + l, c.begin() + r);
        int s0 = ask(0, c);
        ask(1, {t});
        int s1 = ask(0, c);
        return abs(s0-s1);
    };

    vector<int> c(n,1);

    while(accumulate(c.begin(), c.end(),0) != 1) {

        // int tot = 0;
        // for(int i = 0; i < n; i++) {
        //     if(c[i]) tot += adj[i].size();
        // }
        // int rand = rng() % tot;
        // int t = -1;
        // for(int i = 0; i < n; i++) {
        //     if(c[i]) {
        //         rand -= adj[i].size();
        //         if(rand < 0) {
        //             t = i;
        //             break;
        //         }
        //     }
        // }

        int t = -1, ss = INT_MAX;
        
        auto dfsss = [&](auto self, int i, int p) -> int {
            if(c[i] == 0) return 0;
            int res = 1;
            for(int ch : adj[i]) {
                if(ch != p) res += self(self, ch, i);
            }
            return res;
        };

        for(int i = 0; i < n; i++) {
            if(c[i]) {
                int maxss = 0;
                for(int c : adj[i]) maxss = max(maxss, dfsss(dfsss, c, i));
                if(maxss < ss) {
                    t = i;
                    ss = maxss;
                }
            }
        }

        // cout << "try t : " << t << endl;

        vector<int> ch;
        for(int x : adj[t]) ch.push_back(x);

        //see if t is the root
        int diff = get_diff(t, ch, 0, adj[t].size()) / 2;
        // cout << "diff : " << diff << endl;

        if(diff == adj[t].size()) {
            c.assign(n,0);
            c[t] = 1;
            // cout << "stoppage : " << t << endl;
            continue;
        }

        int l = 0, r = adj[t].size() - 1;
        while(l != r) {
            int m = (l + r) / 2;
            int sz = m - l + 1;
            int diff = get_diff(t, ch, l, m + 1) / 2;
            if(diff == sz) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        auto dfs = [&](auto self, int i, int p) -> void {
            c[i] = 0;
            for(int ch : adj[i]) {
                if(ch != p) self(self, ch, i);
            }
        };

        dfs(dfs, t, ch[l]);

    }


    int rt = -1;
    for(int i = 0; i < n; i++) if(c[i]) rt = i;

    // cout << "root is : " << rt << endl;

    vector<int> res(n);

    auto dfs = [&](auto self, int i, int p, int pq) -> void {
        int q = ask(0, {i});
        res[i] = q - pq;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, q);
            }
        }
    };

    dfs(dfs, rt, -1, 0);

    cout << "!";
    for(int x : res) cout << " " << x;
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}