#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, w; cin >> n >> w;

    vector<vector<int>> adj(n);
    vector<int> p(n,-1);

    for(int i = 1; i < n; i++) {
        int par; cin >> par;
        par--;
        p[i] = par;
        adj[par].push_back(i);
    }

    vector<int> depths(n);

    auto assigndepths = [&](auto self, int i, int d) -> void {
        depths[i] = d;
        for(int c : adj[i]) {
            self(self, c, i + 1);
        }
    };

    assigndepths(assigndepths, 0, 0);

    vector<vector<int>> useedge(n);
    vector<int> freedom(n);

    for(int i = 0; i < n; i++) {
        int a = i, b = (i + 1) % n;

        while(depths[a] > depths[b]) {
            useedge[a].push_back(i);
            freedom[i]++;
            a = p[a];
        }

        while(depths[b] > depths[a]) {
            useedge[b].push_back(i);
            freedom[i]++;
            b = p[b];
        }

        while(a != b) {
            useedge[a].push_back(i);
            useedge[b].push_back(i);
            freedom[i]++;
            freedom[i]++;
            a = p[a];
            b = p[b];
        }

    }

    ll ans = 0;
    vector<ll> pathweights(n);
    ll numfree = n;

    for(int i = 1; i < n; i++) {
        ll x, y; cin >> x >> y;
        for(int edge : useedge[x - 1]) {
            freedom[edge]--;
            ans += y;
            if(freedom[edge] == 0) {
                numfree--;
            }
        }
        w -= y;
        // cout << "x : " << x << " y : " << y << " numfree : " << numfree
        cout << ans + numfree * w << " \n"[i == n - 1];
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}