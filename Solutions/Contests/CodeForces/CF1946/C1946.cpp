#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int dfs(int i, int p, vector<vector<int>> &adj, int &k, int x) {
    int csz = 1;
    for(int c : adj[i]) {
        if(c != p) {
            int sz = dfs(c,i,adj,k,x);
            if(sz >= x && k) {
                k--;
                sz = 0;
            }
            csz += sz;
        }
    }
    if(i == 0) {
        if(csz < x) k = 1;
    }
    return csz;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int lo = 1, hi = n;
    while(lo != hi) {
        int m = (lo + hi + 1) / 2;
        int cuts = k;
        int left = dfs(0,-1,adj,cuts,m);
        if(cuts == 0) {
            lo = m;
        } else {
            hi = m - 1;
        }
    }
    cout << lo << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}