#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    ll pos = 1;
    ll add = 0;
    for(int i = 0; i < k; i++) {
        pos += add;
        while(add < n && pos >= v[add]) {
            pos++;
            add++;
        }
        
    }
    cout << pos << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}