#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int odd_cnt = 0;
    for(int i = 0; i < n; i++) {
        odd_cnt += adj[i].size() & 1;
    }

    int a = odd_cnt / 2;

    auto poss = [&](int mp) -> bool {
        int ok = 1;

        auto dfs = [&](auto self, int i, int p) -> int {
            vector<int> child_paths;
            for(int c : adj[i]) {
                if(c != i) {
                    child_paths.push_back(self(self, c, i));
                }
            }

            while()

        };
    };
    
    int l = 1, r = n - 1;
    while(l != r) {
        int m = (l + r + 1) / 2;
        if(poss(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << a << " " << l << '\n';

    return 0;
}