#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int sm = INT_MAX;
    for(int i = 0; i < n / 2 + 5; i++) {
        queue<vector<int>> q;
        q.push({rand() % n,0,-1});
        vector<int> visited(n,-1);
        while(q.size()) {
            vector<int> p = q.front();
            q.pop();
            if(visited[p[0]] != -1) {
                sm = min(sm, p[1] + visited[p[0]]);
                continue;
            }
            visited[p[0]] = p[1];
            for(auto x : adj[p[0]]) {
                if(x != p[2]) {
                    q.push({x,p[1] + 1,p[0]});
                }
            }
        }
    }
    if(sm == INT_MAX) {
        cout << "-1\n";
    } else {
        cout << sm << "\n";
    }
    return 0;
}