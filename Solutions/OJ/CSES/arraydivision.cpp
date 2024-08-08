#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;

    vector<ll> a(n);

    for(ll &x : a) cin >> x;

    ll lo = *max_element(a.begin(), a.end()), hi = 2e14;
    while(hi != lo) {
        ll m = (lo + hi) / 2;
        ll curr = 0;
        int blocks = 1;
        for(int i = 0; i < n; i++) {
            if(curr + a[i] > m) {
                blocks++;
                curr = a[i];
            } else {
                curr += a[i];
            }
        }
        // cout << "m : " << m << " blocks : " << blocks << '\n';
        if(blocks <= k) {
            hi = m;
        } else {
            lo = m + 1;
        }
    }

    cout << lo << '\n';

    return 0;
}