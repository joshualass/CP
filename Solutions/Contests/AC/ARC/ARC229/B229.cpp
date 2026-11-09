#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll ops = 0;
    while(accumulate(a.begin(), a.end(), 0LL)) {

        ll mx = LLONG_MAX;
        for(int i = 0; i < n; i++) {
            ll here = (a[i] << i) + (1 << i) - 1;
            mx = min(here, mx);
        }

        // cout << "a : " << a << " mx : " << mx << endl;

        if(mx == 0) break;

        ll hereops = LLONG_MAX;
        ll t = mx;
        for(int i = 0; i < n && t; i++) {
            hereops = min(hereops, a[i] / t);
            t /= 2;
        }

        // cout << "hereops : " << hereops << endl;

        ops += hereops;
        for(int i = 0; i < n; i++) {
            a[i] -= mx * hereops;
            mx /= 2;
        }

        // ll cur = -1;
        // ll cnt = 0;

        // for(int i = n - 1; i >= 0; i--) {
        //     if(cur == -1) {
        //         if(a[i]) {
        //             if(i + 1 < n) {
        //                 cur = a[i];
        //                 cnt = a[i];
        //             } else {
        //                 cur = a[i];
        //                 cnt = 1;
        //             }
        //         }
        //     } else {
        //         ll add = max(0LL, min(cnt, a[i] - cur));
        //         cur += add;
        //     }

        //     if(cur != -1) {
        //         if(a[i] < cur) {
        //             cout << "-1\n";
        //             return;
        //         } else {
        //             a[i] -= cur;
        //             cur *= 2;
        //         }
        //     }
        // }

        // ops += cnt;
        // cout << "a : " << a << endl;
    }

    if(accumulate(a.begin(), a.end(), 0LL)) {
        cout << "-1\n";
        return;
    }

    cout << ops << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}