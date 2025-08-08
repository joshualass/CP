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
    vector<set<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    int ok = 1;
    for(int i = 0; i < n; i++) {
        if(adj[i].size() & 1) ok = 0;
    }

    vector<int> res;
    
    auto dfs = [&](auto self, int i) -> void {
        while(adj[i].size()) {
            int c = *adj[i].begin();
            adj[i].erase(c);
            adj[c].erase(i);
            self(self, c);
            // res.push_back(i);
            res.push_back(c);
        }
    };

    dfs(dfs, 0);
    res.push_back(0);
    reverse(res.begin(), res.end());

    // auto dfs = [&](auto self, int i) -> void {

    // };

    if(ok && res.size() == m + 1) {
        for(int i = 0; i < res.size(); i++) cout << res[i] + 1 << " \n"[i == res.size() - 1];
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
