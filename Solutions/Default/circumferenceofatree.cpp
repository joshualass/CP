#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;


//returns depth, node
pair<int,int> dfs(int n, int p, int d, vector<vector<int>> &adj) {
    pair<int,int> m = {d, n};
    for(int i : adj[n]) {
        if(i != p) {
            m = max(m, dfs(i, n, d + 1, adj));
        }
    }
    return m;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.first << " " << p.second << " ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    pair<int,int> start = dfs(0,-1,0,adj);
    // cout << dfs(0,-1,0,adj) << "\n";
    
    cout << dfs(start.second, -1, 0, adj).first * 3 << "\n";

    return 0;
}