#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ll inf = 1e18;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--; 
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<pair<ll,int>> s(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        s[i] = {num, i};
    }
    sort(s.begin(), s.end());
    vector<ll> dists(n, inf);
    dists[0] = 0;

    for(int i = n - 1; i >= 0; i--) {
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        vector<bool> visited(n);
        pq.push({dists[s[i].second], s[i].second});
        while(pq.size()) {
            pair<ll,int> p = pq.top();
            pq.pop();
            if(!visited[p.second]) {
                visited[p.second] = 1;
                if(p.first < dists[p.second]) {
                    dists[p.second] = p.first;
                }
                for(auto edge : adj[p.second]) {
                    pq.push({p.first + edge.second * s[i].first, edge.first});
                }
            }
        }
    }
    cout << dists.back() << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}