#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll dfs(int i, int p, int step, int k, vector<vector<int>> &adj) {
    if(step == k) return 1;
    ll cnt = 0;
    for(auto node : adj[i]) {
        if(node != p) {
            cnt += dfs(node, i, step + 1, k, adj);
        }
    }
    return cnt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    ll cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += dfs(i, -1, 0, k, adj);
    }

    cout << cnt / 2 << '\n';

    return 0;
}