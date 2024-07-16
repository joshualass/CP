#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n; cin >> n;

    vector<ll> res(1,n);

    while(1) {
        ll prev = res.back();
        ll next = 0;
        for(int bit = 0; bit < 63; bit++) {
            if((n >> bit) & 1 && (((prev >> bit) & 1) == 0)) {
                next |= 1LL << bit;
            }
        }
        for(int bit = 62; bit >= 0; bit--) {
            if((n >> bit) & 1 && ((next | (1LL << bit)) < prev)) {
                next |= 1LL << bit;
            }
        }
        if(next >= prev || next == 0) break;
        res.push_back(next);
    }
    cout << res.size() << '\n';
    reverse(res.begin(), res.end());
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}