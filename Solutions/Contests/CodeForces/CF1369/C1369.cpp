#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<int> w(k);
    for(int &x : w) cin >> x;

    sort(a.rbegin(), a.rend());
    sort(w.begin(), w.end());

    ll res = 0;
    int p = 0;

    for(int i = 0; i < k; i++) {
        res += a[p];
        w[i]--;
        if(w[i] == 0) res += a[p];
        p++;
    }

    for(int i = 0; i < k; i++) {
        if(w[i]) {
            res += a[p + w[i] - 1];
            p += w[i];
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