#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,0});
    vector<bool> visited(n+1);
    set<int> found;
    while(pq.size()) {
        pair<int,int> top = pq.top();
        pq.pop();
        if(top.first > 3) {
            continue;
        }
        if(visited[top.second]) {
            continue;
        }
        found.insert(top.second);
        visited[top.second] = true;
        for(int x : adj[top.second]) {
            pq.push({top.first+1, x});
        }
    }
    cout << found.size() - 1<< "\n";
    
    for(int x : found) {
        if(x != 0) {

            cout << x << " ";
        }
    }
    cout << "\n";
    return 0;
}