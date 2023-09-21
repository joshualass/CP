#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, x; cin >> n >> x;
    vector<ll> v(n);
    for(auto &y: v) cin >> y;
    sort(v.begin(),v.end());
    pair<ll,ll> prev = {0,x};
    for(int i = 0; i < n; i++) {
        ll diff = v[i] - prev.first;
        if(prev.second - i * diff >= 0) {
            prev = {v[i], prev.second - i * diff};
        } else {
            cout << prev.first + prev.second / i << "\n";
            return;
        }
    }
    cout << prev.first + prev.second / n << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}