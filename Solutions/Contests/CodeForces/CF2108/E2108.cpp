#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
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

    int start = -1;
    vector<int> ss(n);

    auto dfs0 = [&](auto self, int i, int p) -> void {
        int mx = 0, cnt = 0;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                mx = max(mx, ss[c]);
                cnt += ss[c];
            }
        }
        mx = max(mx, n - 1 - cnt);
        if(mx <= n / 2) start = i;
        ss[i] = cnt + 1;
    };

    dfs0(dfs0, 0, -1);

    // cout << "start : " << start << '\n';

    int nl = -1, np = -1, nd = INT_MAX;

    auto dfs1 = [&](auto self, int i, int p, int d) -> void {
        if(adj[i].size() == 1 && d < nd) {
            nl = i;
            np = p;
            nd = d;
        }
        for(int c : adj[i]) {
            if(c != p) self(self, c, i, d + 1);
        }
    };

    dfs1(dfs1, start, -1, 0);

    // cout << "nl : " << nl << " np : " << np << " nd : " << nd << '\n';

    vector<vector<int>> st;

    auto dfs2 = [&](auto self, int i, int p, vector<int> &cur) -> void {
        if(i == nl) {
            cur.push_back(start);
        } else {
            cur.push_back(i);
        }
        for(int c : adj[i]) {
            if(c != p) self(self, c, i, cur);
        }
    };

    priority_queue<array<int,2>> pq;

    for(int c : adj[start]) {
        vector<int> cur;
        dfs2(dfs2, c, start, cur);
        st.push_back(cur);
        pq.push({(int)st.back().size(), (int)st.size() - 1});
    }
    
    vector<int> res(n);
    int pt = 1;

    while(pq.size()) {
        auto [sz1, g1] = pq.top();
        pq.pop();
        auto [sz2, g2] = pq.top();
        pq.pop();
        res[st[g1].back()] = pt;
        res[st[g2].back()] = pt;
        st[g1].pop_back();
        st[g2].pop_back();
        pt++;
        if(st[g1].size()) pq.push({(int) st[g1].size(), g1});
        if(st[g2].size()) pq.push({(int) st[g2].size(), g2});
    }

    if(nl < np) swap(res[nl], res[np]);

    cout << nl + 1 << " " << np + 1 << '\n';
    for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}