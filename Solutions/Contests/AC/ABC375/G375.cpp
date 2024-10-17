#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
During imp. have to consider edge id's
First, do a dijkstra. 
Then, we have to find all the edges that CAN be used in a shortest path. 
We only consider edges that connect in the shortest path. Then, we consider all edges that reach a node that can reach the node N in the shortest path. 


*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void dfsb(int i, int p, vector<vector<array<int,2>>> &adj, vector<int> &low, vector<int> &d, int &time) {
    d[i] = time++;
    low[i] = d[i];

    for(auto [x,id] : adj[i]) {
        if(x != p) {
            if(d[x] == -1) {
                dfsb(x,i,adj,low,d,time);
            }
            // if()
            low[i] = min(low[i], low[x]);
        }
    }

}

vector<int> find_bridges(vector<vector<array<int,2>>> &adj) {
    int n = adj.size();
    vector<int> low(n,-1);
    vector<int> d(n,-1);
    int time = 0;

    for(int i = 0; i < n; i++) {
        if(d[i] == -1) {
            dfsb(i,-1,adj,low,d,time);
        }
    }

    vector<int> res;
    for(int i = 0; i < adj.size(); i++) {
        for(auto[x,id] : adj[i]) {
            if(low[x] > d[i]) {
                // res[x].push_back(i);
                // res[i].push_back(x);
                // cout << "bridge id : " << id << '\n';
                res.push_back(id);
            }
        }
    }

    return res;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<map<int, array<ll,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        if(adj[a].count(b) == 0 || adj[a][b][0] > c) {
            adj[a][b] = {c,i};
        }
        swap(a,b);
        if(adj[a].count(b) == 0 || adj[a][b][0] > c) {
            adj[a][b] = {c,i};
        }
    }

    vector<ll> dists(n,-1);
    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
    pq.push({0,0});
    while(pq.size()) {
        auto [t,i] = pq.top();
        // cout << "i : " << i << " t : " << t << '\n';
        pq.pop();
        if(dists[i] != -1) continue;
        dists[i] = t;
        for(auto [to, stat] : adj[i]) {
            // cout << "to : " << to << " s1 : " << stat[0] << " s2 : " << stat[1] << '\n';
            if(dists[to] == -1) {
                pq.push({t + stat[0], to});
            }
        }
    }

    // cout << "dists : " << dists << '\n';

    vector<int> reachable(n,-1);
    reachable[n-1] = 1;
    vector<vector<array<int,2>>> adj2(n);
    auto dfs = [&](auto self, int i) -> void {

        int ok = 0;
        for(auto [to, stat] : adj[i]) {
            if(dists[i] + stat[0] == dists[to]) {
                if(reachable[to] == -1) {
                    self(self, to);
                }
                if(reachable[to]) {
                    // cout << "i : " << i << " to : " << to << " ok now\n";
                    ok = 1;
                    adj2[i].push_back({to, (int) stat[1]});
                    adj2[to].push_back({i, (int) stat[1]});
                    // cout << "add edge : " << i << ", " << to << '\n';
                }
            }
        }

        reachable[i] = ok;

    };

    dfs(dfs, 0);

    // cout << "reachable : " << reachable << '\n';

    vector<int> bridge_ids = find_bridges(adj2);
    vector<int> res(m);
    for(int x : bridge_ids) {
        // cout << "x : " << x << '\n';
        res[x] = 1;
    }
    for(int x : res) {
        cout << (x ? "Yes" : "No") << '\n';
    }

    return 0;
}