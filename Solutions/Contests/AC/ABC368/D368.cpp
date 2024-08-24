#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);

    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> isk(n);
    int begin = -1;
    for(int i = 0; i < k; i++) {
        int num; cin >> num;
        isk[num - 1] = 1;
        begin = num - 1;
    }
    int removes = 0;
    auto dfs = [&](auto self, int i, int p) -> int {

        int cnt = isk[i];
        for(int c : adj[i]) {
            if(c != p) { 
                cnt += self(self, c, i);
            }
        }
        if(cnt == 0) removes++;
        return cnt;
    };

    dfs(dfs, begin, -1);

    cout << n - removes << '\n';

    return 0;
}