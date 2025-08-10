#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> cnts(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        cnts[a]++;
        cnts[b]--;
    }

    int ok = 1;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            if(cnts[i] != 1) ok = 0;
        } else if(i == n - 1) {
            if(cnts[i] != -1) ok = 0;
        } else {
            if(cnts[i]) ok = 0;
        }
    }

    vector<int> res;
    int f = 0;

    auto dfs = [&](auto self, int i) -> void {
        while(adj[i].size()) {
            int c = adj[i].back();
            adj[i].pop_back();
            self(self, c);
            res.push_back(i);
        }
        if(f == 0) {
            if(i != n - 1) ok = 0;
            f = 1;
        }
    };

    dfs(dfs, 0);

    reverse(res.begin(), res.end());
    res.push_back(n - 1);
    if(ok && res.size() == m + 1) {
        for(int i = 0; i < res.size(); i++) cout << res[i] + 1 << " \n"[i == res.size() - 1];
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
