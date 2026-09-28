#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    int ops = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(i == 0) {
            ops += x != 1;
        } else {
            x--;
            adj[i].push_back(x);
            adj[x].push_back(i);
        }
    }

    auto dfs = [&](auto self, int i, int p) -> int {
        int furthest = 1;
        for(int c : adj[i]) {
            if(c != p) {
                furthest = max(furthest, self(self, c, i));
            }
        }
        if(i) {
            if(furthest == k) {
                ops += p != 0;
                return 1;
            } else {
                return furthest + 1;
            }
        }
        return -1;
    };

    dfs(dfs, 0, -1);

    cout << ops << '\n';

    return 0;
}