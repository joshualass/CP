#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> ma(1 << n, 100);

    auto check = [&](vector<int> &a) -> int {
        int res = 0;
        for(int i = 0; i < a.size(); i++) {
            int cur = a[i], nx = a[(i + 1) % a.size()];
            int f = 0;
            for(int j : adj[cur]) if(j == nx) f = 1;
            if(f == 0) res++;
        }
        return res;
    };

    auto dfs = [&](auto self, vector<int> &a, int bm) -> void {
        if(a.size() >= 3) {
            ma[bm] = min(ma[bm], check(a));
        }
        for(int i = 0; i < n; i++) {
            if(((bm >> i) & 1) == 0) {
                a.push_back(i);
                bm += 1 << i;
                self(self, a, bm);
                a.pop_back();
                bm -= 1 << i;
            }
        }
    };

    vector<int> a;
    dfs(dfs, a, 0);

    for(int i = 0; i < 1 << n; i++) {
        for(int j = 0; j < 1 << n; j++) {
            if((i & j) == j) {
                ma[i] = min(ma[i], ma[j] + ma[i ^ j]);
            }
        }
    }

    cout << ma[(1 << n) - 1] + (m + ma[(1 << n) - 1] - n) << '\n';

    return 0;
}
