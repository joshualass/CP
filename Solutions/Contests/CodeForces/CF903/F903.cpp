#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

pair<int,int> dfs(int n, int p, int d, vector<vector<int>> &adj) {
    pair<int,int> m = {d, n};
    for(int i : adj[n]) {
        if(i != p) {
            m = max(m, dfs(i, n, d + 1, adj));
        }
    }
    return m;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<bool> marked(n);
    int firstmark = -1;
    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        marked[--num] = true;
        firstmark = num;
    }
    vector<set<int>> adj(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 1) {
            q.push(i);
        }
    }
    while(q.size()) {
        int i = q.front();
        q.pop();
        if(!marked[i]) {
            int next = *adj[i].begin();
            adj[i].erase(next);
            adj[next].erase(i);
            if(adj[next].size() == 1) {
                q.push(next);
            }
        }
    }
    vector<vector<int>> adj2(n);
    for(int i = 0; i < n; i++) {
        for(auto x : adj[i]) {
            adj2[i].push_back(x);
        }
    }
    pair<int,int> start = dfs(firstmark,-1,0,adj2);
    // cout << dfs(0,-1,0,adj) << "\n";
    
    cout << (dfs(start.second, -1, 0, adj2).first + 1) / 2 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}