#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<pair<ll,pair<ll,ll>>>> adj(n);
    for(int i = 0; i < m; i++) {
        ll a, b, x , y; cin >> a >> b >> x >> y;
        a--; b--;
        adj[a].push_back({b,{x,y}});
        adj[b].push_back({a,{-x,-y}});
    }
    vector<pair<ll,ll>> coords(n,{LLONG_MAX,LLONG_MAX});
    coords[0] = {0,0};
    queue<int> q;
    q.push(0);
    while(q.size()) {
        int f = q.front();
        q.pop();
        for(auto x : adj[f]) {
            if(coords[x.first].first == LLONG_MAX && coords[x.first].second == LLONG_MAX) {
                coords[x.first] = {coords[f].first + x.second.first, coords[f].second + x.second.second};
                q.push(x.first);
            }
        }
    }
    for(auto x : coords) {
        if(x.first == LLONG_MAX) {
            cout << "undecidable\n";
        } else {
            cout << x.first << " " << x.second << "\n";
        }
    }

    return 0;
}