#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> vis(1 << n);
    string res(n - 1, '0');

    auto dfs = [&](auto self, int x) -> void {
        res.push_back('0' + (x & 1));
        vis[x] = 1;
        int nx_base = (x & (((1 << (n - 1)) - 1))) << 1;
        // cout << "x : " << x << '\n';
        if(vis[nx_base + 1] == 0) {
            self(self, nx_base + 1);
        } else if(vis[nx_base] == 0) {
            self(self, nx_base);
        }
    };

    dfs(dfs, 0);

    cout << res << '\n';

    return 0;
}
