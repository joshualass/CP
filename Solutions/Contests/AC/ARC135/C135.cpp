#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> bitcnts(30);

    vector<ll> v(n);

    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = num;
        for(int j = 0; j < 30; j++) {
            if((num >> j) & 1) {
                bitcnts[j]++;
            }
        }
    }

    ll ans = reduce(v.begin(), v.end());

    for(int i = 0; i < n; i++) {
        ll sum = 0;
        for(int bit = 0; bit < 30; bit++) {
            ll amt = -1;
            if((v[i] >> bit) & 1) {
                amt = n - bitcnts[bit];
            } else {
                amt = bitcnts[bit];
            }
            sum += amt * (1 << bit);
        }
        ans = max(ans, sum);
    }
    cout << ans << '\n';
    return 0;
}