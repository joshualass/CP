#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n), h(n);
    for(auto &x: a) cin >> x;
    for(auto &x: h) cin >> x;

    vector<bool> div(n-1);

    for(int i = 0; i < n - 1; i++) {
        if(h[i] % h[i+1] == 0) {
            div[i] = 1;
        }
    }
    int ans = 0;
    if(*min_element(a.begin(),a.end()) <= k) {
        ans = 1;
    }
    int l = 0, r = 0;
    int fruit_cnt = a[0];

    for(int i = 0; i < n - 1; i++) {
        if(div[i]) {
            r++;
            fruit_cnt += a[i+1];
        } else {
            l = i + 1;
            r = i + 1;
            fruit_cnt = a[i+1];
        }
        while(fruit_cnt > k) {
            fruit_cnt -= a[l++];
        }
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}