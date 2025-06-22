#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, w; cin >> n >> w;
    vector<vector<ll>> a(61);

    for(int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        a[x].push_back(y);
    }

    ll res = 0;

    for(int i = 0; i < 60; i++) {
        sort(a[i].begin(), a[i].end());
        if(a[i].size() && ((w >> i) & 1)) {
            res += a[i].back();
            a[i].pop_back();
        }
        while(a[i].size()) {
            ll z = 0;
            for(int j = 0; j < 2; j++) {
                if(a[i].size()) {
                    z += a[i].back();
                    a[i].pop_back();
                } 
            }
            a[i+1].push_back(z);
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}