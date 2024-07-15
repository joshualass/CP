#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// {distance, a}
array<int,2> dfs(int i, int p, int d, vector<vector<int>> &adj) {
    array<int,2> res = {d, i};
    for(int c : adj[i]) {
        if(c != p) {
            res = max(res, dfs(c,i,d+1,adj));
        }
    }
    return res;
}

//{a, b, diameter}
array<int,3> find_diamter(vector<vector<int>> &adj) {
    array<int,2> a = dfs(0,-1,0,adj);
    array<int,2> b = dfs(a[1],-1,0,adj);
    return {a[1], b[1], b[0]};
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
    
    array<int,3> diameter = find_diamter(adj);

    cout << diameter[2] << '\n';

    return 0;
}