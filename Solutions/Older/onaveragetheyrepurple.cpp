#include <bits/stdc++.h>
typedef long long ll;
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
    set<int> visited;
    queue<pair<int,int>> q;
    q.push({1,0});
    int num = -1;
    while(true) {
        pair<int,int> p = q.front();
        q.pop();
        if(p.first == n) {
            num = p.second;
            break;
        }
        if(visited.find(p.first) != visited.end()) {
            continue;
        }
        visited.insert(p.first);
        for(int x : adj[p.first]) {
            q.push({x,p.second+1});
        }
    }
    cout << --num;
    return 0;
}