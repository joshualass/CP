#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, root; cin >> n >> root;
    root--;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    ll l = 0;

    auto cangetallzeroes = [&](ll m) -> ll {
        auto dfs = [&](auto self, int i, int p) -> ll {
            ll sum = a[i] - (m + n - i - 1) / n;
            for(int c : adj[i]) {
                if(c != p) {
                    sum += self(self, c, i);
                }
            }
            if(sum <= 0) {
                return abs(sum) & 1;
            }
            return sum;
        };
        return dfs(dfs, root, -1);
    };

    while(1) {
        ll bruh = cangetallzeroes(l);
        if(bruh == 0) {
            cout << l << '\n';
            return;
        }
        l += bruh;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}