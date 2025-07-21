#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(n, -1);
    queue<array<int,2>> cur, nx0, nx1;

    cur.push({0, 0});

    int t = 0;

    while(1) {
        while(cur.size()) {
            auto [i, wait] = cur.front();
            cur.pop();
            // cout << "i : " << i << " t : " << t << " wait : " << wait << '\n';
            if(i == n - 1) {
                cout << t << " " << wait << '\n';
                return;
            }
            //go
            nx0.push({adj[i][t % adj[i].size()], wait});
            //wait
            nx1.push({i, wait + 1});
        } 

        t++;

        dp.assign(n, -1);

        while(nx0.size() || nx1.size()) {
            int nxi, nxw;
            if(nx1.empty()) {
                auto [i, wait] = nx0.front();
                nx0.pop();
                nxi = i, nxw = wait;
            } else if(nx0.empty()) {
                auto [i, wait] = nx1.front();
                nx1.pop();
                nxi = i, nxw = wait;
            } else if(nx0.front()[1] <= nx1.front()[1]) {
                auto [i, wait] = nx0.front();
                nx0.pop();
                nxi = i, nxw = wait;
            } else {
                auto [i, wait] = nx1.front();
                nx1.pop();
                nxi = i, nxw = wait;
            }
            if(dp[nxi] == -1) {
                dp[nxi] = nxw;
                cur.push({nxi, nxw});
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}