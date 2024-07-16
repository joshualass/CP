#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//skillfully capped here

void dfs(int i, int p, vector<vector<int>> &adj, vector<ll> &a, vector<array<ll,20>> &dp) {

    array<ll,20> res = {a[i], a[i] * 2, a[i] * 3, a[i] * 4, a[i] * 5, a[i] * 6, a[i] * 7, a[i] * 8, a[i] * 9, a[i] * 10, a[i] * 11, a[i] * 12, a[i] * 13, a[i] * 14, a[i] * 15, a[i] * 16, a[i] * 17, a[i] * 18, a[i] * 19, a[i] * 20};



    for(int c : adj[i]) {
        if(c != p) {

            dfs(c,i,adj,a,dp);

            for(int j = 0; j < 20; j++) {
                ll lo = LLONG_MAX;
                for(int k = 0; k < 20; k++) {
                    if(k != j) {
                        lo = min(lo, dp[c][k]);
                    }
                }
                res[j] += lo;
            }
        }
    }

    dp[i] = res;

}

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<array<ll,20>> dp(n);

    dfs(0,-1,adj,a,dp);

    cout << *min_element(dp[0].begin(), dp[0].end()) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}