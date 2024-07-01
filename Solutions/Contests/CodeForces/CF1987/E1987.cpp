#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll INF = 1e13;

/*
return from dfs - 
an array of length n storing that if I need to increase this child, how many times can I do this operation at a cost from 1 - n
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<ll> dfs(int i, int p, vector<vector<int>> &adj, ll &res, int &n, vector<ll> &a) {
    if(adj[i].size() == 1 && i != 0) {//leaf
        vector<ll> ops(n,INF);
        ops[0] = 0;
        return ops;
    }

    vector<ll> children(n);
    ll sumc = 0;
    for(int c : adj[i]) {
        if(c != p) {
            vector<ll> cops = dfs(c,i,adj,res,n,a);
            for(int j = 0; j < n; j++) {
                children[j] += cops[j];
            }
            sumc += a[c];
        }
    }
    // cout << "a[i] : " << a[i] << " sumc : " << sumc << '\n';
    // cout << "children : " << children << '\n';
    ll nops = 0;
    for(int j = 0; j < n; j++) {
        ll ops = max(0LL, min(a[i] - sumc, children[j]));
        // cout << "i : " << j << " ops : " << ops << '\n';
        nops += ops * j;
        sumc += ops;
        children[j] -= ops;
    }
    res += nops;
    // cout << "i : " << i << " nops : " << nops << '\n';

    vector<ll> ops(n);
    for(int j = 1; j < n; j++) {
        ops[j] = children[j-1];
    }
    ops[1] = sumc - a[i];
    return ops;
}

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }

    ll res = 0;
    dfs(0,-1,adj,res,n,a);
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}