#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll sops = (*min_element(a.begin(), a.end())) / (n - 1);
    ll res = sops * 2;
    for(ll &x : a) x -= sops * (n - 1);

    auto min_ops = [&]() -> ll {
        ll best = LLONG_MAX;
        if(a[0] == 0) {
            ll min_ops = 0;
            for(int i = 1; i < n; i++) {
                min_ops = max(min_ops, (a[i] + i - 1) / i);
            }
            best = min_ops;
        }
        for(int i = 1; i < n; i++) {
            
        }
    };


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi--) solve();

    return 0;
}