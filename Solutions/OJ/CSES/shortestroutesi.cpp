#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    vector<vector<pair<ll,ll>>> adj(n);
    vector<ll> times(n,-1);
    for(ll i = 0; i < m; i++) {
        ll a,b,c;cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b,c});
    }
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    pq.push({0,0});
    while(pq.size()) {
        pair<ll,ll> p = pq.top();
        pq.pop();
        if(times[p.second] == -1) {
            times[p.second] = p.first;
            for(auto x : adj[p.second]) {
                pq.push({p.first + x.second, x.first});
            }
        }
    }
    for(auto x : times) cout << x << " ";
    return 0;
}