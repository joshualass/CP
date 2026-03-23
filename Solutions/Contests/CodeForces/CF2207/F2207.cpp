#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> r(n * m), c(n * m);
    for(auto &x : r) cin >> x;
    for(auto &x : c) cin >> x;

    vector<vector<int>> p(m);
    for(int i = 0; i < n * m; i++) {
        p[c[i] - 1].push_back(r[i] - 1);
    }

    vector<int> bad(n);
    vector<vector<int>> ip(m, vector<int>(n));
    
    for(int i = 0; i < m; i++) {
        int mx = -1;
        for(int j = 0; j < n; j++) {
            if(p[i][j] < mx) {
                bad[p[i][j]] = 1;
            }
            mx = max(mx, p[i][j]);
            ip[i][p[i][j]] = j;
        }
    }

    int ops = n;
    int rem = n - accumulate(bad.begin(), bad.end(), 0);
    vector<int> a(rem - 1, -1);

    for(int i = 0; i < m; i++) {
        int blocked = 0, idx = -1;
        for(int j = 0; j < n; j++) {
            if(j && ip[i][j] < ip[i][j-1]) {
                blocked = 1;
            }
            if(bad[j] == 0) {
                if(idx >= 0) a[idx] += blocked;
                idx++;
                blocked = 0;
            }
        }
    }

    int cost = m - 1;

    // int cur = 0, mn = 0;
    // for(int i = 0; i < sz(a); i++) {
    //     cur += a[i];
    //     if(cur > 0) {
    //         cur = 0, mn = 0;
    //     } else if(cur > mn + cost) {
    //         ops += mn + cost;
    //         cur = 0, mn = 0;
    //     }
    //     mn = min(mn, cur);
    // }

    // if(mn < -cost) {
    //     ops += mn + cost;
    // }

    if(n == 66665) {
        cout << "a:";
        for(int x : a) cout << x << "_";
        cout << '\n';
    }

    ll inactive = 0, active = inf;
    for(int x : a) {
        ll nx_active = min(active + x, inactive + x + cost);
        ll nx_inactive = min(inactive, active);
        active = nx_active;
        inactive = nx_inactive;
    }

    cout << ops - 1 + min(active, inactive) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}