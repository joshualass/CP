#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<vector<pair<int,int>>>> adj(n,vector<vector<pair<int,int>>>(m));
    vector<vector<int>> rocks(n,vector<int>(m));
    for(auto &x : rocks) for(int &y : x) cin >> y;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(j != m - 1 && rocks[(i+1)%n][j+1] != 1) {
                adj[i][j].push_back({(i+1)%n,j+1});
            }
            if(rocks[(i+1) % n][j] != 1 && rocks[(i+2)%n][j] != 1) {
                adj[i][j].push_back({(i+2)%n,j});
            }
        }
    }
    vector<vector<int>> visited(n,vector<int>(m,-1));
    queue<pair<int,pair<int,int>>> q;
    q.push({0,{0,0}});
    while(q.size()) {
        pair<int,pair<int,int>> p = q.front();
        q.pop();
        int steps = p.first;
        pair<int,int> coords = p.second;
        if(visited[coords.first][coords.second] != -1) continue;
        visited[coords.first][coords.second] = steps;
        for(auto to : adj[coords.first][coords.second]) {
            q.push({steps+1,{to.first,to.second}});
        }
    }
    int ans = INT_MAX;
    for(int i = 0; i < n; i++) {
        if(visited[i][m-1] != -1) {
            int realrow = i - visited[i][m-1];
            while(realrow < 0) realrow += n;
            ans = min(ans, visited[i][m-1] + min((n - 1 - realrow), realrow + 1));
        }
    }
    cout << (ans == INT_MAX ? -1 : ans) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}