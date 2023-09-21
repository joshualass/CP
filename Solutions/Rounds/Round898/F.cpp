#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, k; cin >> n >>k;
    vector<ll> a(n), h(n);
    for(auto &x: a) cin >> x;
    for(auto &x: h) cin >> x;
    int most = 0;
    int l = 0;
    ll cnt = a[0];
    for(int i = 1; i < n; i++) {
        if(h[i-1] % h[i] == 0) {
            cnt += a[i];
            while(cnt > k) {
                cnt -= a[l++];
            }
            most = max(most, i - l + 1);
        } else {
            while(cnt > k && l < i) {
                cnt -= a[l++];
            }
            most = max(most, i - l);
            l = i;
            cnt = a[i];
        }
    }
    cout << most << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}