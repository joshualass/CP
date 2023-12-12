#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, s, k; cin >> n >> s >> k;

    ll sum = 0;
    for(int i = 0; i < n; i++) {
        ll p, q; cin >> p >> q;
        sum += p * q;
    }
    if(sum < s) {
        sum += k;
    }
    cout << sum << '\n';

    return 0;
}