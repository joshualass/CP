#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    
    for(ll &x : a) cin >> x;
    bool ak = 1;
    for(int i = 0; i < n; i++) {
        if(a[i] != k) ak = 0;
    }

    if(ak) {
        cout << "0\n";
        return;
    }

    bool isover = 1;
    bool notposs = 0;
    vector<ll> v;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            if(a[i] < k) {
                isover = 0;
            }
        }
        if(isover) {
            v.push_back(a[i] - k);
            if(a[i] <= k) {
                notposs = 1;
            }
        } else {
            v.push_back(k - a[i]);
            if(a[i] >= k) {
                notposs = 1;
            }
        }
    }
    if(notposs) {
        cout << "-1\n";
        return;
    }
    ll g = v[0];
    for(int i = 1; i < n; i++) {
        g = gcd(g, v[i]);
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        ans += v[i] / g;
    }
    cout << ans - n << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}