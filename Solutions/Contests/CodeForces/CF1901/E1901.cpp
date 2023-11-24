#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//let first be most of taking 1
//let second be most of taking 2+

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

pair<ll,ll> dfs(int i, int p, vector<vector<int>> &adj, vector<ll> &v) {

    vector<pair<ll,ll>> children;
    for(auto x : adj[i]) {
        if(x != p) {
            children.push_back(dfs(x,i,adj,v));
        }
    }

    ll first_max = 0;
    ll second_sum = 0;

    for(auto p : children) {
        first_max = max(first_max,p.first);
        second_sum += max(0LL,p.second);
    }
    pair<ll,ll> ans = {max(first_max,v[i]), second_sum + v[i]};
    cout << "i : " << i << " ans : " << ans << '\n';
    cout << "children : " << children << '\n';
    return ans;
}

void solve() {
    int n; cin >> n;
    vector<ll> v(n);

    for(auto &x : v) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    pair<ll,ll> p = dfs(0, -1, adj, v);

    cout << p << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}