#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[201][201]; //node, time

pair<int,vector<int>> hungarian(const vector<vector<int>> &a) {
    if(a.empty()) return {0,{}};
    int n = a.size() + 1, m = a[0].size() + 1;
    vector<int> u(n), v(m), p(m), ans(n-1);
    for(int i = 1; i < n; i++) {
        p[0] = i;
        int j0 = 0; 
        vector<int> dist(m, INT_MAX), pre(m, -1);
        vector<bool> done(m + 1);
        do {
            done[j0] = true;
            int i0 = p[j0], j1, delta = INT_MAX;
            for(int j = 1; j < m; j++) if(!done[j]) {
                auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if(cur < dist[j]) dist[j] = cur, pre[j] = j0;
                if(dist[j] < delta) delta = dist[j], j1 = j;
            }
            for(int j = 0; j < m; j++) {
                if(done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            }
            j0 = j1;
        } while(p[j0]);
        while(j0) {
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    for(int j = 1; j < m; j++) if(p[j]) ans[p[j] - 1] = j - 1;
    return {-v[0], ans};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> c(n+1),d(n+1);
    vector<vector<int>> adj(n+1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i] >> d[i];
        int p; cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }

    auto dfs = [&](auto self, int i, int p) -> void {
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }

        int ss = adj[i].size();
        if(i != 0) ss--;
        for(int j = 0; j <= n; j++) {
            int initial_anger = c[i] * (d[i] - j) * (d[i] - j);

            dp[i][j] = INT_MAX;
            if(j + ss <= n) {
                vector<vector<int>> match;
                int ok = 1;
                for(int c : adj[i]) {
                    if(c != p) {
                        match.push_back({});
                        for(int k = 0; k < ss; k++) {
                            match.back().push_back(dp[c][j+k+1]);
                            if(dp[c][j+k+1] == INT_MAX) {
                                ok = 0;
                            }
                        }
                    }
                }
                if(ok) {
                    auto [cost, matching] = hungarian(match);
                    dp[i][j] = initial_anger + cost;
                }
            } 
        }
    };

    dfs(dfs,0,-1);

    cout << dp[0][0] << '\n';

    return 0;
}