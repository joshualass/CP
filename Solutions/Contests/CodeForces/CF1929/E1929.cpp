#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void find_parents(int i, int p, vector<vector<int>> &adj, vector<int> &parents) {
    parents[i] = p;
    for(int x : adj[i]) {
        if(x != p) {
            find_parents(x,i,adj,parents);
        }
    }
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
    vector<int> parents(n);
    find_parents(0,-1,adj,parents);
    vector<int> subsets(n);
    int k; cin >> k;
    int bit = 1;
    for(int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        while(a != 0) {
            subsets[a] ^= bit;
            a = parents[a];
        }
        while(b != 0) {
            subsets[b] ^= bit;
            b = parents[b];
        }
        bit <<= 1;
    }
    sort(subsets.begin(), subsets.end());
    subsets.erase(unique(subsets.begin(),subsets.end()), subsets.end());

    vector<int> dp(1 << k, 1e9);
    dp[0] = 0;
    for(int i = 0; i < dp.size(); i++) {
        for(int subset : subsets) {
            int to = i | subset;
            dp[to] = min(dp[to],dp[i]+1);
        }
    }
    cout << dp.back() << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}