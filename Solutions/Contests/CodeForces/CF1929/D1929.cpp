#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
/*TREE dp wowowowowowowowo*/

//TODO replace with template that supports all modular operations
ll binexp(ll base, ll power, ll MOD = MOD) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

//returns a / b using modular inverse. this implementation uses fermat's little theorem
ll modDivide(ll a, ll b, ll MOD = MOD) {
    return binexp(b,MOD-2,MOD) * a % MOD;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void tree_dp(int i, int p, vector<vector<int>> &adj, vector<vector<ll>> &dp) {
    dp[i][0] = 1; //1 way to make 0 (always)
    ll poss = 1;
    for(int x : adj[i]) {
        if(x != p) {
            tree_dp(x,i,adj,dp);
            dp[i][2] += dp[x][2];
            dp[i][2] += dp[x][1];
            poss *= dp[x][0] + dp[x][1];

            poss %= MOD;
            dp[i][0] %= MOD;
            dp[i][1] %= MOD;
            dp[i][2] %= MOD;
        }
    }
    dp[i][1] = poss;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<vector<ll>> dp(n,vector<ll>(3)); //{ways to make with 0, 1, 2, subtreesize}
    tree_dp(0,-1, adj,dp);
    // cout << "dp : " << dp << '\n';
    cout << reduce(dp[0].begin(), dp[0].end()) % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}