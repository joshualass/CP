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
    for(auto x : v) os << x << " ";
    return os;
}

void calcdis(vector<vector<pair<int,int>>> &adj, vector<pair<int,int>> &vis, int start) {
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    pq.push({0, start, -1});
    while(pq.size()) {
        array<int,3> a = pq.top();
        pq.pop();
        if(vis[a[1]].first == -1) {
            vis[a[1]] = {a[0], a[2]};
            for(auto p : adj[a[1]]) {
                if(vis[p.first].first == -1) {
                    pq.push({a[0] + p.second, p.first, a[1]});
                }
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<pair<int,int>> sd(n,{-1,-1});
    vector<pair<int,int>> ed(n,{-1,-1});

    calcdis(adj,sd,0);
    calcdis(adj,ed,n-1);

    // cout << "sd : " << sd << '\n';
    // cout << "ed : " << ed << '\n';

    int best = sd.back().first;
    if(best == -1) {
        cout << best << '\n';
        return 0;
    }

    int curr = n - 1;
    int prev = -1;
    int d2 = INT_MAX;
    while(curr != -1) {
        for(auto p : adj[curr]) {
            if(p.first != sd[curr].second && p.first != prev) {
                d2 = min(d2, ed[curr].first + sd[p.first].first + p.second);
            }
        }
        prev = curr;
        curr = sd[curr].second;
    }

    if(d2 == INT_MAX) {
        cout << "-1\n";
        return 0;
    }
    // cout << "optimal : " << sd.back().first << " alt : " << d2 << '\n';
    cout << sd.back().first + d2 << '\n';
    return 0;
}