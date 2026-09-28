#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<vector<int>> adj(n);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> w(n);
    vector<pair<int,int>> sw(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        w[i] = num;
        sw[i] = {num,i};
    }

    vector<ll> ops(n);
    sort(sw.begin(), sw.end());

    vector<vector<ll>> dp(5001,vector<ll>(5001));

    for(int l = 0; l < n; l++) {
        int i = sw[l].second;
        for(int j = 0; j < adj[i].size(); j++) {
            for(int k = 1; k <= 5000; k++) {
                dp[j+1][k] = max({dp[j][k],dp[j+1][k-1], (w[adj[i][j]] <= k ? dp[j][k-w[adj[i][j]]] + ops[adj[i][j]] : 0)});
            }
        }
        ops[i] = dp[adj[i].size()][w[i]-1] + 1;
    }

    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        ans += a * ops[i];
    }

    cout << ans << '\n';

    return 0;
}