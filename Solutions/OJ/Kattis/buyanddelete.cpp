#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;

signed main() {

    int ans = 0;
    int n, m, ic;
    cin >> n >> m >> ic;
    vector<vector<pll>> c(n);
    for(int i = 0; i < m; i++){
        int u, v, p;
        cin >> u >> v >> p;
        u --, v --;
        c[u].push_back({v, p});
        if(p <= ic) ans = 1;
    }
    vl d(n);
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) d[j] = 1e18, v[j] = false;
        priority_queue<pll> q; //{-dist, ind}
        for(int j = 0; j < c[i].size(); j++) {
            int next = c[i][j].first;
            d[next] = min(d[next], c[i][j].second);
            // cout << "Q PUSH : " << next << " " << c[i][j].second << " " << d[next] << "\n";
            q.push({-c[i][j].second, next});
        }
        // cout << "Q SZ : " << q.size() << "\n";
        while(q.size() != 0) {
            int cur = q.top().second;
            ll cdist = -q.top().first;
            q.pop();
            // cout << "CUR : " << cur << " " << cdist << " " << d[cur] << "\n";
            if(cdist != d[cur]) continue;
            if(v[cur]) continue;
            // cout << "IN\n";
            v[cur] = true;
            for(pll x : c[cur]) {
                ll ndist = cdist + x.second;
                int next = x.first;
                // cout << "NEXT : " << next << "\n";
                if(ndist < d[next]) {
                    d[next] = ndist;
                    q.push({-ndist, next});
                }
            }
        }
        if(d[i] <= ic) ans = 2;
        // for(int j = 0; j < n; j++) cout << d[j] << " ";
        // cout << "\n";
    }
    cout << ans << "\n";

    return 0;
}