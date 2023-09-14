#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int counter;
vector<vector<int>> adj (0);
vector<int> visited;
vector<int> order;
vector<int> low;
bool bridge;

void DFS2(int n, int p) {
    visited[n] = true;
    order[n] = counter;
    low[n] = counter++;
    for(int x : adj[n]) {
        if(x == p) {
            continue;
        }
        if(visited[x]) {
            low[n] = min(low[n], order[x]);
        } else {
            DFS2(x, n);
            low[n] = min(low[n], low[x]);
            if(low[x] > order[n]) bridge = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int p, c; cin >> p >> c;
    while(p != 0 || c != 0) {
        adj.assign(p,{});
        visited.assign(p,false);
        order.assign(p,-1);
        low.assign(p,-1);
        counter = 0;
        bridge = false;
        for(int i = 0; i < c; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        for(int i = 0; i < p; i++) {
            if(!visited[i]) {
                DFS2(i,-1);
            }
        }
        cout << (bridge ? "Yes" : "No") << "\n";
        cin >> p >> c;
    }

    return 0;
}