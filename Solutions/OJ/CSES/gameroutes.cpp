#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    vector<int> topological = topological_sort(adj);

    // cout << "top: " << topological << '\n';

    vector<int> dp(n);
    dp[0] = 1;

    for(int i = 0; i < n; i++) {
        int node = topological[i];
        for(auto x : adj[node]) {
            dp[x] += dp[node];
            if(dp[x] >= MOD) {
                dp[x] -= MOD;
            }
        }
    }

    cout << dp.back() << '\n';

    return 0;
}