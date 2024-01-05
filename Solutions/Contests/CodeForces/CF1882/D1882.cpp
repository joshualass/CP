#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void dfs1(int i, int p, vector<vector<int>> &adj, vector<ll> &v, vector<pair<int,ll>> &costs) {
    pair<int,ll> cost = {1,0}; //subtree size, total cost
    for(int child : adj[i]) {
        if(child != p) {
            dfs1(child, i, adj, v, costs);
            // cost += (v[i] ^ v[child]) + costs[child];
            cost.first += costs[child].first;
            cost.second += (v[i] ^ v[child]) * costs[child].first + costs[child].second;
        }
    }
    costs[i] = cost;
}

void dfs2(int i, int p, vector<vector<int>> &adj, vector<ll> &v, vector<pair<int,ll>> &costs) {
    if(p != -1) {
        ll parent_subtree_size = costs[p].first - costs[i].first;
        ll parent_score = costs[p].second;
        //undo child subtree from parent, first the operation, then the subtree, but it is added back later so don't do
        parent_score -= (v[i] ^ v[p]) * costs[i].first;
        //now add operation + subtree
        parent_score += (v[i] ^ v[p]) * parent_subtree_size;
        costs[i] = {costs[p].first, parent_score};
    }
    for(int child : adj[i]) {
        if(child != p) {
            dfs2(child, i, adj, v, costs);
        }
    }
}

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

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) { //for trees
    // for(int i = 0; i < m; i++) { //for graphs with m edges
        int a, b; cin >> a >> b;
        a--; b--; //1 -> 0 indexed
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<pair<int,ll>> costs(n);

    dfs1(0,-1,adj,v,costs);
    // cout << "costs 1 : " << costs << '\n';
    dfs2(0,-1,adj,v,costs);
    // cout << "costs 2 : " << costs << '\n';

    for(int i = 0; i < n; i++) {
        cout << costs[i].second << " \n"[i == n-1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}