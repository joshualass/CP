#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void color(int i, int p, vector<vector<int>> &adj,vector<int> &dist, int d, int &ans) {
    if(d >= ans || dist[i] <= d) return;
    ans = min(ans, d + dist[i]);
    dist[i] = d;
    for(int c : adj[i]) {
        if(d + 1 >= ans) break;
        if(c != p) {
            color(c,i,adj,dist,d+1,ans);
        }
    }
}

void solve() {

    int n, c0; cin >> n >> c0;
    vector<int> order(n-1);
    for(int &x : order) cin >> x;
    vector<vector<int>> adj(n+1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> dist(n+1,1e9);

    int ans = INT_MAX;
    color(c0,-1,adj,dist,0,ans);
    for(int i = 0; i < n - 1; i++) {
        color(order[i],-1,adj,dist,0,ans);
        cout << ans << " \n"[i == n - 2];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(chrono::steady_clock::now().time_since_epoch().count());
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}