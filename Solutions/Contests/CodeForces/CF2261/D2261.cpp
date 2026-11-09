#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

// void solve() {
    
//     int n, m; cin >> n >> m;
//     if(n == 1) {
//         cout << "0\n";
//         return;
//     }
//     cout << (n + 1) / 2 << '\n';
//     for(int i = 0; i < (n + 1) / 2; i++) {
//         int len = (n + 1) / 2;
//         cout << 1 + i << " " << 1 + i + len - 1 << "\n";
//     }

// }

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n, m; cin >> n >> m;
    vector<ll> a(n + 1);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--;
        ll x = rng() / 3;
        a[u] ^= x;
        a[v] ^= x;
    }

    ll cur = 0;
    vector<ll> b(n);
    vector<int> c;
    set<ll> s;
    for(int i = 0; i < n; i++) {
        //consider the segment from i to i + 1
        cur ^= a[i];
        b[i] = cur;
        if(s.count(cur)) {
            c.push_back(i);
            s.clear();
        }
        s.insert(cur);
    }
    int add = sz(c) & 1;
    if(!c.empty()) {
        s.clear();
        for(int i = 0; i < c[0]; i++) {
            s.insert(b[i]);
        }
        for(int i = c.back(); i < n; i++) {
            if(s.count(b[i])) add = 1;
        }
    }
    if(add) {
        c.push_back(n);
    }
    if(sz(c) & 1) {
        c.insert(c.begin(), 0);
    }
    
    assert(sz(c) % 2 == 0);
    cout << sz(c) / 2 << '\n';
    for(int i = 0; i < sz(c) / 2; i++) {
        cout << c[i] + 1 << " " << c[i + sz(c) / 2] << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}