#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> hasfather(n);
    for(int i = 0; i < m; i++) {
        int p, q; cin >> p >> q;
        p--; q--;
        adj[p].push_back(q);
        hasfather[q] = 1;
    }

    vector<int> g(n);
    vector<int> toadd(n);
    for(int &x : g) {
        cin >> x;
        x--;
        toadd[x] = 1;
    }

    vector<int> order(n,-1);
    vector<int> res;

    auto dfs = [&](auto self, int i) -> void {
        for(int c : adj[i]) {
            self(self, c);
        }
        if(toadd[i]) {
            toadd[i] = 0;
            order[i] = res.size();
            res.push_back(i);
        }
    };

    for(int i = 0; i < n; i++) {
        if(hasfather[i] == 0) {
            dfs(dfs, i);
        }
    }

    // cout << "res : " << res << '\n';
    // cout << "order : " << order << '\n';

    int ok = 1;

    auto dfs2 = [&](auto self, int i, int ca) -> void {
        if(order[i] != -1) {
            ca = min(ca, order[i]);
        }
        if(res[ca] != g[i]) {
            ok = 0;
            // cout << "bad i : " << i << " ca : " << ca << '\n';    
        }
        for(int c : adj[i]) {
            self(self, c, ca);
        }
    };

    for(int i = 0; i < n; i++) {
        if(hasfather[i] == 0) {
            dfs2(dfs2, i, INT_MAX);
        }
    }

    if(ok) {
        cout << res.size() << '\n';
        for(int x : res) cout << x + 1 << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}