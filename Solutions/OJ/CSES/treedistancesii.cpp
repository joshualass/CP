#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void dfs1(int i, int par, vector<vector<int>> &adj, vector<pair<int,ll>> &cnts) {
    pair<int,ll> p = {1,0};
    for(int child : adj[i]) {
        if(child != par) {
            dfs1(child, i, adj, cnts);
            p.first += cnts[child].first;
            p.second += cnts[child].first + cnts[child].second;
        }
    }
    cnts[i] = p;
}

void dfs2(int i, int par, vector<vector<int>> &adj, vector<pair<int,ll>> &cnts) {
    if(par != -1) {
        pair<int,ll> p = {cnts[par].first - cnts[i].first + 1, cnts[par].first + cnts[par].second - (cnts[i].first * 2 + cnts[i].second)}; 
        for(int child : adj[i]) {
            if(child != par) {
                p.first += cnts[child].first;
                p.second += cnts[child].first + cnts[child].second;
            }
        }
        cnts[i] = p;
    }
    for(int child : adj[i]) {
        if(child != par) {
            dfs2(child, i, adj, cnts);
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

    vector<pair<int,ll>> cnts(n,{-1,-1});
    dfs1(0,-1,adj,cnts);
    // cout << "cnts1 : " << cnts << '\n';
    dfs2(0,-1,adj,cnts);
    // cout << "cnts2 : " << cnts << '\n';

    for(int i = 0; i < n; i++) {
        cout << cnts[i].second << " \n"[i == n - 1];
    }

    return 0;
}