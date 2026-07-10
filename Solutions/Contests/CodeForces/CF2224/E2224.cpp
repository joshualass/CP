#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 2e18;

void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> p(n, -1);
    vector<ll> l(n, -1);

    for(int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for(int i = 1; i < n; i++) cin >> l[i];

    vector<vector<pair<int,ll>>> adj(n);

    for(int i = 1; i < n; i++) {
        int par = p[i];
        ll len = l[i];
        adj[par].push_back({i, len});
    }

    vector<vector<pair<int,ll>>> nx_adj(n);

    //len is the actual length of the path. r is the offset from m that allows access to this path. 
    auto dfs = [&](auto self, int i, ll p, ll r, ll len) -> pair<int,ll> {
        ll s = sz(adj[i]);
        if(s == 0) {
            return {i, len};
        } else {
            ll g = gcd(p, s);
            if(p == inf || p / g > inf / s) { //inf
                int child = (r + len) % s;
                return self(self, adj[i][child].first, inf, r, len + adj[i][child].second);
            } else if(g == 1) { //forced decision
                int child = (r + len) % s;
                return self(self, adj[i][child].first, p, r, len + adj[i][child].second);
            } else {

                
                for(int j = 0; j < )
                
            }
        }


    };

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}