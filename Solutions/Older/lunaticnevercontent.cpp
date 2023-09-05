#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void prllV(const vector<ll> &x) {
    cout << " --- vector --- \n";
    for(ll y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

void solve() {
    ll n; cin >> n;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    ll mod = 0;
    // prllV(v);
    for(ll i = 0; i < n/2; i++) {
        if(v[i] == v[n-i-1]) {
            continue;
        }
        if(mod == 0) {
            mod = max(v[i],v[n-i-1]) - min(v[i],v[n-i-1]);
        } else {

            mod = gcd(mod,max(v[i],v[n-i-1]) - min(v[i],v[n-i-1]));
        }
    }
    cout << mod << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) {
        solve();
    }
    return 0;
}