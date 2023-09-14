#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int counter;
vector<int> dsu;
vector<vector<int>> adj (0);
vector<int> visited;
vector<int> order;
vector<int> low;
bool bridge;

int find(int x) {
    if(x == dsu[x]) {
        return x;
    } else {
        dsu[x] = find(dsu[x]);
        return dsu[x];
    }
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    dsu[y] = x;
}


void DFS2(int n, int p) {
    // if(visited[n]) {
    //     return;
    // }
    // cout << "?";
    visited[n] = true;
    order[n] = counter;
    low[n] = counter++;
    for(int x : adj[n]) {
        if(x == p) {
            continue;
        }
        // if(!visited[x]) {
        //     DFS2(x,n);
        // }
        // low[n] = min(low[n],low[x]);
        // if(low[x] > order[n]) {
        //     bridge = true;
        // }
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
    // cout << "here 6" << "\n";

    int p, c; cin >> p >> c;
    while(p != 0 || c != 0) {
        // cout << "here 7" << "\n";
        adj.clear();adj.resize(p); //cout << "adj size: " << adj.size() << '\n';
        dsu.clear(); dsu.resize(p);
        // cout << "here 1" << "\n";
        for(int i = 0; i < p; i++) {
            dsu[i] = i;
        }
        // cout << "here 2" << "\n";
        for(int i = 0; i < c; i++) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
            // cout << "a: " << a << " b: " << b << '\n';
            merge(a,b);
        }
        // cout << "here 3" << "\n";
        visited.clear();visited.resize(p);
        order.clear(); order.resize(p);
        low.clear(); low.resize(p);
        counter = 0;
        bridge = false;
        // cout << "here?";

        //bad
        DFS2(0,-1);
        //good
        for(int i = 0; i < p; i++) {
            if(!visited[i]) {
                DFS2(i,-1);
            }
        }
        // for(int i = 1; i < p; i++) {
        //     if(find(i) != find(i-1)) {
        //         bridge = false;
        //     }
        // }
        // cout << "here 4" << "\n";
        // for(int r = 0; r < adj.size(); r++) {
        //     for(int i = 0; i < adj[r].size(); i++) {
        //         if(low[adj[r][i]] > low[r]) {
        //             cout << "r: " << r << " i: " << i << " adj: " << adj[r][i] << '\n';
        //             bridge = true;
        //         }
        //     }
        // }
        cout << (bridge ? "Yes" : "No") << "\n";
        cin >> p >> c;
    }

    return 0;
}