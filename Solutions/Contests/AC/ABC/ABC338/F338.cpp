#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e18 + 7;
const ll MAXN = 20;
ll dp[1 << MAXN][MAXN];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    //all pairs shortest path - apsp. solve using floyd warshal
    vector<vector<ll>> dist(n,vector<ll>(n,1e18));
    for(ll i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        dist[u][v] = w;
    }
    for(ll i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for(ll k = 0; k < n; k++) {
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); //at each iteration k, tries to make element k an llermediate node, like mat exp
            }
        }
    }

    for(int i = 0; i < 1 << MAXN; i++) {
        for(int j = 0; j < n; j++) {
            dp[i][j] = 1e18;
        }
    }
    for(ll i = 0; i < n; i++) {
        dp[1 << i][i] = 0; 
    }

    for(ll bm = 1; bm < 1 << n; bm++) {
        for(ll i = 0; i < n; i++) {
            if((bm & (1 << i)) == 0 || dp[bm][i] == 1e18) continue;
            for(ll j = 0; j < n; j++) {
                // if(dist[i][j] == 1e18) continue;
                if((bm & (1 << j)) == 0) {
                    // cout << "bm : " << bm << " from : " << i << " to : " << j << " to bm : " << (bm | (1 << j))<< " curr val : " << dp[bm][i] << " try val : " << dp[bm][i] + dist[i][j] << '\n';
                    dp[bm | (1 << j)][j] = min(dp[bm | (1 << j)][j], dp[bm][i] + dist[i][j]);
                }
            }
        }
    }
    ll ans = 1e18;
    for(ll i = 0; i < n; i++) {
        // cout << "end at : " << i << " val : " << dp[(1 << n) - 1][i] << '\n';
        ans = min(ans, dp[(1 << n) - 1][i]);
    }
    cout << (ans == 1e18 ? "No" : to_string(ans)) << '\n';
    return 0;
}