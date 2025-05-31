#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, q; cin >> n >> q;

    vector<int> b(n);
    for(int &x : b) cin >> x;

    vector<array<int,3>> qs(q);
    vector<vector<int>> adj(n);
    for(int i = 0; i < q; i++) {
        int x, y, z; cin >> x >> y >> z;
        x--; y--; z--;
        qs[i] = {x, y, z};
        adj[z].push_back(0);
    }

    for(int i = 0; i < n; i++) {
        adj[i].push_back(b[i]);
    }

    for(int i = q - 1; i >= 0; i--) {
        auto [x, y, z] = qs[i];
        int need = adj[z].back();
        adj[z].pop_back();
        adj[x].back() = max(adj[x].back(), need);
        adj[y].back() = max(adj[y].back(), need);
    }

    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = adj[i][0];

    vector<int> check = a;
    
    for(int i = 0; i < q; i++) {
        auto [x, y, z] = qs[i];
        check[z] = min(check[x], check[y]);
    }

    if(check == b) {
        for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}