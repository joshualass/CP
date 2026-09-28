#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 1e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

void dfs(int i, bool curr, int p, vector<vector<int>> &adj, vector<bool> &comps) {
    comps[i] = curr;
    for(auto x : adj[i]) {
        if(x != p) {
            dfs(x, curr ^ 1, i, adj, comps);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    factorial();
    
    int n; cin >> n;
    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> comps(n);

    dfs(0,1,-1,adj,comps);
    ll size0 = 0;
    ll size1 = 0;
    for(int i = 0; i < n; i++) {
        if(comps[i]) {
            size1++;
        } else {
            size0++;
        }
    }

    cout << factorials[size0] * factorials[size1] * 2 % MOD << '\n';



    return 0;
}