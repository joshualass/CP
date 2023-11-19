#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    ll most = 0;

    for(int size = 1; size <= n; size++) {
        if(n % size == 0) {
            ll lo = LLONG_MAX;
            ll hi = LLONG_MIN;
            ll curr = 0;
            for(int i = 0; i < n; i++) {
                curr += v[i];
                if((i+1) % size == 0) {
                    lo = min(lo,curr);
                    hi = max(hi,curr);
                    curr = 0;
                }
            }
            most = max(most, hi - lo);
        }
    }
    cout << most << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}