#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//minimal side effect topological sort
void _topological(int i, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &ans) {
    // cout << "top sort: " << i << '\n';
    visited[i] = true;
    for(auto x : adj[i]) {
        if(!visited[x]) {
            _topological(x,adj,visited,ans);
        }
    }
    ans.push_back(i);
}

vector<int> topological_sort(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n);
    vector<int> ans;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            _topological(i, adj, visited, ans);
        }
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c, m; cin >> n >> c >> m;
    vector<int> a(n);
    for(int i = 0; i < c; i++) {
        int x; cin >> x;
        a[x-1] = 1;
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    vector<int> topo = topological_sort(adj);

    vector<int> lo(n,1e9), hi(n,a[0]);
    lo[0] = a[0];
    int s = 0;

    for(int i = 0; i < n; i++) {
        int j = topo[i];
        if(j == 0) s = 1;
        if(s) {
            for(int c : adj[j]) {
                lo[c] = min(lo[c], lo[j] + a[c]);
                hi[c] = max(hi[c], hi[j] + a[c]);
            }
        }
    }

    cout << lo[n-1] << '\n' << hi[n-1] << '\n';

    return 0;
}