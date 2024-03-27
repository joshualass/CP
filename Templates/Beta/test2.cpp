#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

void dfsb(int i, int p, vector<vector<int>> &adj, vector<int> &low, vector<int> &d, int &time) {
    d[i] = time++;
    low[i] = d[i];

    for(int x : adj[i]) {
        if(x != p) {
            if(d[x] == -1) {
                dfsb(x,i,adj,low,d,time);
            }
            // if()
            low[i] = min(low[i], low[x]);
        }
    }

}

vector<vector<int>> find_bridges(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> low(n,-1);
    vector<int> d(n,-1);
    int time = 0;

    for(int i = 0; i < n; i++) {
        if(d[i] == -1) {
            dfsb(i,-1,adj,low,d,time);
        }
    }

    dfsb(0,-1,adj,low,d,time);
    // cout << "d : " << d << '\n' << "low : " << low << '\n';

    vector<vector<int>> res(n);
    for(int i = 0; i < adj.size(); i++) {
        for(int x : adj[i]) {
            if(low[x] > d[i]) {
                res[x].push_back(i);
                res[i].push_back(x);
            }
        }
    }

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<vector<int>> bridges = find_bridges(adj);

    cout << "bridges\n";
    for(int i = 0; i < n; i++) {
        for(int x : bridges[i]) {
            cout << "bridge from : " << i << " to : " << x << '\n';
        }
    }

    return 0;
}