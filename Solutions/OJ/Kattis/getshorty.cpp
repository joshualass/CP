#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    while(n != 0) {
        vector<vector<pair<int,ld>>> adj(n);
        for(int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            ld f; cin >> f;
            ld logf = log(f);
            adj[a].push_back({b,logf});
            adj[b].push_back({a,logf});
        }
        priority_queue<pair<ld,int>> pq;
        pq.push({0,0});
        vector<ld> vis(n,1);
        while(pq.size()) {
            pair<ld,int> p = pq.top();
            pq.pop();
            if(vis[p.second] != 1) continue;
            vis[p.second] = p.first;
            for(pair<int,ld> x : adj[p.second]) {
                if(vis[x.first] == 1) {
                    pq.push({x.second + p.first, x.first});
                }
            }
        }
        cout << fixed << setprecision(4) << exp(vis[n-1]) << '\n';
        cin >> n >> m;
    }

    return 0;
}