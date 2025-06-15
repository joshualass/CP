#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
kind of an adjust the knobs problem. 
need to be able to do math on paper before coding /!\

If all the ratios of A_i / B_i for all i are the same, then it is clearly impossible. Ax will always be that same ratio of Bx. 
If there exist i and j such that their ratios differ, then we should always be able to construct a sequence by only having these 
2 indices be nonzero. 

There are no negatives, so all the ratios will be positive. In order to solve the above, we should first compare their ratios A_i / B_i and A_j / B_j
and compare with a simple cross multiplication. Now that we know the lower and higher ratios, we should intuitively, put a negative value with the lower ratio
and a positive value for the higher ratio, but how should we choose these?

We should look to see which of the ratios is "larger" than the other, a ratio is larger if the smaller ratio has a larger a value or the larger ratio has a larger b value
We use these values because 

*/

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    ll d = 0;
    for(ll i = 0; i < n; i++) {
        ll g0 = gcd(a[0], b[0]), gi = gcd(a[i], b[i]);
        if(a[0] / g0 != a[i] / gi || b[0] / g0 != b[i] / gi) d = i;
    }

    if(d) {
        cout << "Yes\n";

        ll l, h;

        if(a[0] * b[d] > a[d] * b[0]) {
            h = 0, l = d;
        } else {
            h = d, l = 0;
        }

        ll lm, hm;

        if(a[l] < b[h]) {
            lm = 3999999;
            hm = (a[l] * lm) / a[h] + 1;
            lm = (a[h] * hm + a[l] - 1) / a[l] - 1;
            // hm = (a[l] * lm) / a[h] + 1;
        } else {
            hm = 3999999;
            lm = (b[h] * hm) / b[l] + 1;
            hm = (b[l] * lm + b[h] - 1) / b[h] - 1;
        }

        lm *= -1;

        ll ax = 0, bx = 0;

        for(int i = 0; i < n; i++) {
            ll x;
            if(i == l) {
                x = lm;
            } else if(i == h) {
                x = hm;
            } else {
                x = 0;
            }
            ax += a[i] * x, bx += b[i] * x;
            cout << x << " \n"[i == n - 1];
        }

        // cout << "ax : " << ax << " bx : " << bx << '\n';

        assert(ax > 0 && bx < 0);

        assert(abs(lm) <= 1e8 && abs(hm) <= 1e8);

    } else {
        cout << "No\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}