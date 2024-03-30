#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
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

vector<set<int>> find_bridges(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> low(n,-1);
    vector<int> d(n,-1);
    int time = 0;

    for(int i = 0; i < n; i++) {
        if(d[i] == -1) {
            dfsb(i,-1,adj,low,d,time);
        }
    }

    cout << "d : " << d << '\n' << "low : " << low << '\n';

    vector<set<int>> res(n);
    for(int i = 0; i < adj.size(); i++) {
        for(int x : adj[i]) {
            if(low[x] > d[i]) {
                res[x].insert(i);
                res[i].insert(x);
            }
        }
    }

    return res;
}

int nodes = 0;
void DFS2(int n, vector<bool> &visited, vector<set<int>> &bridges, vector<vector<int>> &adj) {
    if(visited[n]) {
        return;
    }
    nodes++;
    visited[n] = true;
    for(int x : adj[n]) {
        if(bridges[n].find(x) == bridges[n].end()) {
            // cout << "not found: " << n << " " << x << "\n";
            DFS2(x,visited,bridges,adj);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N);
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<set<int>> bridges = find_bridges(adj);

    

    vector<bool> vis(N);
    DFS2(0,vis,bridges,adj);
    cout << nodes;

    return 0;
}