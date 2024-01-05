#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

void dfs1(int i, int par, vector<vector<int>> &adj, vector<pair<int,ll>> &cnts) {
    pair<int,ll> p = {1,0};
    for(int child : adj[i]) {
        if(child != par) {
            dfs1(child, i, adj, cnts);
            p.first += cnts[child].first;
            p.second += cnts[child].second;
        }
    }
    p.second += p.first;
    cnts[i] = p;
}   

void dfs2(int i, int par, vector<vector<int>> &adj, vector<pair<int,ll>> &cnts) {
    if(par != -1) {
        // pair<int,ll> p = {cnts[par].first - cnts[i].first + 1, cnts[par].second - cnts[i].second * 2 + };
        //treat the parent like a child
        int parent_size = cnts[par].first - cnts[i].first;
        ll parent_score = cnts[par].second - cnts[i].first - cnts[i].second;
        
        pair<int,ll> p = {parent_size, parent_score};
        // cout << "a : " << cnts[par].second << " b : " << cnts[i].first << " c : " << cnts[i].second << '\n';
        // cout << "parent p : " << p << '\n';
        for(int child : adj[i]) {
            if(child != par) {
                p.first += cnts[child].first;
                p.second += cnts[child].second;
            }
        }
        p.first++;
        p.second += p.first;
        // cout << "dfs2 i : " << i << " p : " << p << '\n';
        cnts[i] = p;
    }
    for(int child : adj[i]) {
        if(child != par) {
            dfs2(child, i, adj, cnts);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) { //for trees
    // for(int i = 0; i < m; i++) { //for graphs with m edges
        int a, b; cin >> a >> b;
        a--; b--; //1 -> 0 indexed
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<pair<int,ll>> cnts(n);

    dfs1(0,-1,adj,cnts);
    // cout << "cnts1 : " << cnts << '\n';
    dfs2(0,-1,adj,cnts);
    // cout << "cnts2 : " << cnts << '\n';
    ll ans = 0;

    for(auto p : cnts) {
        ans = max(ans, p.second);
    }
    cout << ans << '\n';
    return 0;
}