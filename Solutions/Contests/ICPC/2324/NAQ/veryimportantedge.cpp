#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }   

    priority_queue<pair<ll,pair<int,int>>, vector<pair<ll,pair<int,int>>>, greater<pair<ll,pair<int,int>>>> pq;
    vector<bool> visited(n);

    for(int i = 0; i < adj[0].size(); i++) {
        pq.push({adj[0][i].second, {0, adj[0][i].first}});
    }

    ll mst = 0;
    ll maxdiff = 0;
    visited[0] = 1;
    while(pq.size()) {
        pair<ll,pair<int,int>> edge = pq.top();
        pq.pop();
        int a = edge.second.first;
        int b = edge.second.second;
        ll c = edge.first;
        if(visited[b]) continue;
        mst += c;
        visited[b] = 1;

        while(pq.size() && visited[pq.top().second.second]) {
            pq.pop();
        }
        
        if(pq.size()) {
            maxdiff = max(maxdiff, pq.top().first - c);
        }
        for(pair<int,ll> edge : adj[b]) {
            pq.push({edge.second, {b, edge.first}});
        }
    }

    cout << mst + maxdiff << '\n';

    return 0;
}