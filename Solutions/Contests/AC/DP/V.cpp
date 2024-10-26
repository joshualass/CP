#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;

void dfs1(int i, int p, vector<vector<int>> &adj, vector<ll> &ways, vector<vector<ll>> &pre, vector<vector<ll>> &suf, vector<int> &order) {
    vector<ll> mults;
    for(int j = 0; j < adj[i].size(); j++) {
        int child = adj[i][j];
        if(child != p) {
            dfs1(child, i, adj, ways, pre, suf, order);
            mults.push_back(ways[child]);
            order[child] = j;
        } else {
            mults.push_back(1);
        }
    }
    ll ans = 1;
    int n = mults.size();
    vector<ll> suffs(n);
    vector<ll> prefs(n);
    for(int j = 0; j < n; j++) {
        ans *= mults[j];
        ans %= MOD;
        if(j == 0) {
            prefs[j] = mults[j] % MOD;
            suffs[n-j-1] = mults[n-j-1] % MOD;
        } else {
            prefs[j] = prefs[j-1] * mults[j] % MOD;
            suffs[n-j-1] = suffs[n-j] * mults[n-j-1] % MOD;
        }
    }
    ways[i] = (ans + 1) % MOD;
    pre[i] = prefs;
    suf[i] = suffs;
}

void dfs2(int i, int p, ll parent_contrib, vector<vector<int>> &adj, vector<ll> &ways, vector<vector<ll>> &pre, vector<vector<ll>> &suf, vector<int> &order) {
    if(p != -1) {
        ll ans = ((ways[i] + MOD - 1) * parent_contrib + 1) % MOD;
        ways[i] = ans;
    }

    for(int child : adj[i]) {
        if(child != p) {
            ll new_parent_contrib = parent_contrib;
            if(order[child] != 0) {
                new_parent_contrib *= pre[i][order[child] - 1];
                new_parent_contrib %= MOD;
            }
            if(order[child] != suf[i].size() - 1) {
                new_parent_contrib *= suf[i][order[child]+1];
                new_parent_contrib %= MOD;
            }
            new_parent_contrib++;
            dfs2(child, i, new_parent_contrib % MOD, adj, ways, pre, suf, order);
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n >> MOD;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) { //for trees
    // for(int i = 0; i < m; i++) { //for graphs with m edges
        int a, b; cin >> a >> b;
        a--; b--; //1 -> 0 indexed
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<ll> ways(n); //number of ways to paint subtree at i 
    vector<vector<ll>> prefs(n);
    vector<vector<ll>> suffs(n);
    vector<int> order(n); //in parents pref/suff stuff.

    dfs1(0,-1,adj,ways,prefs,suffs,order);
    dfs2(0,-1,1,adj,ways,prefs,suffs,order);

    for(int i = 0; i < n; i++) {
        cout << (ways[i] + MOD - 1) % MOD << '\n';
    }

    return 0;
}