#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int res = 0;

    auto dfs = [&](auto self, int i, int p) -> ll {
        ll sum = a[i];
        for(int c : adj[i]) {
            if(c != p) {
                ll d = self(self, c, i);
                if(d % 2 == 0) res++;
                sum += d;
            }
        }
        return sum;
    };

    dfs(dfs, 0, -1);

    if(accumulate(a.begin(), a.end(), 0LL) % 2 == 0) {
        cout << res + 1 << '\n';
    } else {
        cout << "-1\n";
    }
    
    return 0;
}