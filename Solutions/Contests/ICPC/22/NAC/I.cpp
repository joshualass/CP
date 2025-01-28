#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, c; cin >> n >> c;
    vector<array<ll,3>> a;
    ll tt = 0;

    for(int i = 0; i < n; i++) {
        ll t, d; cin >> t >> d;
        tt += t;
        ll f = t / d;
        a.push_back({d, f, 0});
        if(t - f * d) {
            a.push_back({t - f * d, 1, f});
        }
    }

    sort(a.rbegin(), a.rend());

    ll lo = 0, hi = 1e18 / c;
    while(lo != hi) {   
        ll m = (lo + hi) / 2;
        ll t = tt;
        ll rtb = c * m;
        int pc = 0;
        for(auto [d, c, r] : a) {
            if(m == r) {
                t -= d;
                t++;
            } else if(m >= r) { //excludes some remainders 
                ll rb = min({c, m, rtb + pc});
                if(rb > rtb) {
                    pc -= rb - rtb;
                    t += rb - rtb;
                    t -= (rb - rtb) * d;
                    c -= rb - rtb;
                    rb = rtb;
                }
                rtb -= rb;
                c -= rb;
                t -= d * rb;
                if(c) {
                    t++;
                    t -= d;
                } else {
                    pc++;
                }
            }
        }

        if(t <= c) {
            hi = m;
        } else {
            lo = m + 1;
        }
    }
    cout << lo << '\n';
    return 0;
}