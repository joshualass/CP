#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll n, p, l, t; cin >> n >> p >> l >> t;
    ll maxtwotaskdays = ((n + 6) / 7) / 2;
    ll lo = 0, r = n;
    while(lo != r) {
        ll m = (lo + r) / 2;
        ll on_days = n - m;
        ll lessons = on_days;
        ll tasks = 0;
        if(on_days <= maxtwotaskdays) {
            tasks = on_days * 2;
        } else {
            ll lessons_left = (n + 6) / 7 - maxtwotaskdays * 2;
            tasks = maxtwotaskdays * 2 + min(on_days - maxtwotaskdays, lessons_left);

        }
        
        ll score = lessons * l + t * tasks;
        // cout << "rest days : " << m << " on_days : " << on_days << " score : " << score << " lessons : " << lessons << " tasks : " << tasks << '\n';
        if(score < p) {
            r = m;
        } else {
            lo = m + 1;
        }
    }
    cout << lo - 1 << '\n';
}

//         while(lo != hi) { //searching for FFFFFTTTTT first true
//             int m = (lo + hi + 1) / 2;
//             if(query(0,m) < val) {
//                 lo = m;
//             } else {
//                 hi = m - 1;
//             }
//         }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}