#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<vector<int>> adj;
vector<set<int>> bridges;
vector<bool> visited;
vector<int> low;
vector<int> order;
int counter = 0;

void DFS(int n, int p) {
    visited[n] = true;
    low[n] = counter;
    order[n] = counter++;
    for(int x : adj[n]) {
        if(x == p) {
            continue;
        }
        if(visited[x]) {
            low[n] = min(low[n],low[x]);
        } else {
            DFS(x,n);
            low[n] = min(low[n],low[x]);
            if(low[x] > order[n]) {
                // cout << "bridge: " << x << " " << n << "\n";
                bridges[x].insert(n);
                bridges[n].insert(x);
            }
        }
    }
}

int nodes = 0;
void DFS2(int n) {
    if(visited[n]) {
        return;
    }
    nodes++;
    visited[n] = true;
    for(int x : adj[n]) {
        if(bridges[n].find(x) == bridges[n].end()) {
            // cout << "not found: " << n << " " << x << "\n";
            DFS2(x);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    adj.resize(N);
    bridges.resize(N);
    visited.resize(N);
    low.resize(N);
    order.resize(N);
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i =0; i < N; i++) {
        if(!visited[i]) {
            DFS(i,-1);
        }
    }
    visited.assign(N,false);
    DFS2(0);
    cout << nodes;

    return 0;
}