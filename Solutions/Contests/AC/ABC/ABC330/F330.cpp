#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int MAXN = 2e5;

int xs[MAXN];
int ys[MAXN];

ll getops1(int n, ll length) {
    ll lo = 0, hi = 1e9;

    while(hi - lo > 5) {
        ll m1 = lo + (hi - lo) / 3;
        ll m2 = lo + ((hi - lo) * 2 + 1) / 3;
        assert(m1 != m2); ///infinite loop?
        ll m1ops = 0, m2ops = 0;
        for(int i = 0; i < n; i++) {
            if(xs[i] < m1) {
                m1ops += m1 - xs[i];
            }
            if(xs[i] > m1 + length) {
                m1ops += xs[i] - (m1 + length);
            }
        }
        for(int i = 0; i < n; i++) {
            if(xs[i] < m2) {
                m2ops += m2 - xs[i];
            }
            if(xs[i] > m2 + length) {
                m2ops += xs[i] - (m2 + length);
            }
        }
        if(m1ops < m2ops) {
            hi = m2;
        } else {
            lo = m1;
        }
    }

    ll ans = LLONG_MAX;
    for(ll i = lo; i <= hi; i++) {
        ll ops = 0;
        for(int j = 0; j < n; j++) {
            if(xs[j] < i) {
                ops += i - xs[j];
            }
            if(xs[j] > i + length) {
                ops += xs[j] - (i + length);
            }
        }
        ans = min(ans, ops);
    }
    return ans;
    // ll ops = 0;
    // for(int i = 0; i < n; i++) {
    //     if(xs[i] < lo) {
    //         ops += lo - xs[i];
    //     }
    //     if(xs[i] > lo + length) {
    //         ops += xs[i] - (lo + length);
    //     }
    // }
    // return ops;
}

ll getops2(int n, ll length) {
    ll lo = 0, hi = 1e9;

    while(hi - lo > 5) {
        ll m1 = lo + (hi - lo) / 3;
        ll m2 = lo + ((hi - lo) * 2 + 1) / 3;
        assert(m1 != m2); ///infinite loop?
        ll m1ops = 0, m2ops = 0;
        for(int i = 0; i < n; i++) {
            if(ys[i] < m1) {
                m1ops += m1 - ys[i];
            }
            if(ys[i] > m1 + length) {
                m1ops += ys[i] - (m1 + length);
            }
        }
        for(int i = 0; i < n; i++) {
            if(ys[i] < m2) {
                m2ops += m2 - ys[i];
            }
            if(ys[i] > m2 + length) {
                m2ops += ys[i] - (m2 + length);
            }
        }
        if(m1ops < m2ops) {
            hi = m2;
        } else {
            lo = m1;
        }
    }

    ll ans = LLONG_MAX;
    for(ll i = lo; i <= hi; i++) {
        ll ops = 0;
        for(int j = 0; j < n; j++) {
            if(ys[j] < i) {
                ops += i - ys[j];
            }
            if(ys[j] > i + length) {
                ops += ys[j] - (i + length);
            }
        }
        ans = min(ans, ops);
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ll k; cin >> k;

    for(int i = 0; i < n; i++) {
        cin >> xs[i];
        cin >> ys[i];
    }

    ll blo = 0, bhi = 1e9;

    while(blo != bhi) {
        ll m = (blo + bhi) / 2;
        ll length = m;

        ll xops = getops1(n, length);
        ll yops = getops2(n, length);

        // cout << "m : " << m << " xops : " << xops << " yops : " << yops << '\n';

        if(xops + yops <= k) {
            bhi = m;
        } else {
            blo = m + 1;
        }
    }

    cout << blo << '\n';

    return 0;
}