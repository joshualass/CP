#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void dfs(int i, int p, int pp, vector<vector<int>> &adj, vector<vector<int>> &parents, vector<vector<int>> &fo, string &s, vector<int> &cfo) {
    parents[pp][i] = p;
    fo[pp][i] = cfo[s[i] - 'a'];
    for(int v : adj[i]) {
        if(v != p) {
            if(cfo[s[i] - 'a'] == -1) {
                cfo[s[i] - 'a'] = v;
                dfs(v,i,pp,adj,parents,fo,s,cfo);
                cfo[s[i] - 'a'] = -1;
            } else {
                dfs(v,i,pp,adj,parents,fo,s,cfo);
            }
        }
    }
}

void recur(int from, int to, vector<vector<int>> &parents, vector<vector<int>> &fo, string &s, vector<vector<int>> &dp) {
    if(from == to) {
        dp[from][to] = 1;
    } else {
        int use = 0;
        if(fo[from][to] != -1) {
            use = 2;
            if(fo[from][to] != to) {
                if(dp[fo[from][to]][parents[from][to]] == -1) {
                    recur(fo[from][to], parents[from][to], parents, fo, s, dp);
                }
                use += dp[fo[from][to]][parents[from][to]];
            }
        }
        if(dp[from][parents[from][to]] == -1) {
            recur(from,parents[from][to],parents,fo,s,dp);
        }
        int dontuse = dp[from][parents[from][to]];
        // cout << "from : " << from << " to : " << to << " use : " << use << " don't use : " << dontuse << '\n';
        dp[from][to] = max(use,dontuse);
    }
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<vector<int>> parents(n,vector<int>(n));
    vector<vector<int>> fo(n,vector<int>(n));
    vector<vector<int>> dp(n,vector<int>(n,-1));
    vector<int> cfo(26,-1);

    for(int i = 0; i < n; i++) {
        dfs(i,-1,i,adj,parents,fo,s,cfo);
    }

    int res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dp[i][j] == -1) {
                recur(i,j,parents,fo,s,dp);
            }
            res = max(res,dp[i][j]);
        }
    }
    // cout << "dp\n" << dp;

    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}