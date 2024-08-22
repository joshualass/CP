#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
Need a good way to count for this problem. 
One approach is that for each pair of dots i, j, where i != j, 

*/

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    
    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll res = 0;

    for(int i = 0; i < n; i++) {
        int lo = i - 1;
        int hi = i + 1;
        for(int j = i + 1; j < n; j++) {
            while(hi != n && a[hi] - a[j] < a[j] - a[i]) {
                hi++;
            }
            while(lo != -1 && a[i] - a[lo] <= a[j] - a[i]) {
                lo--;
            }

            // cout << "i : " << i << " j : " << j << " lo : " << lo << " hi : " << hi << " ways : " << binexp(2, (n - hi) + (lo - -1)) << '\n';;

            res += binexp(2, (n - hi) + (lo - -1));
        }
    }

    cout << res % MOD << '\n';

    return 0;
}