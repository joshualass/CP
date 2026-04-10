#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

// why upsolve ?

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) {
        cin >> x;
        x *= 2;
    }
    string s; cin >> s;

    vector<ll> gsuf(n + 1);
    for(int i = n - 1; i >= 0; i--) {
        gsuf[i] = gsuf[i+1] + (s[i] == 'G' ? a[i] : 0);
    }

    auto check = [&](ll c) -> ll {
        ll time = 0;
        ll stamina = 0;
        int start = 0;
        int water_vis = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == 'G') {
                ll fly = max(0LL, min(a[i], c - gsuf[i + 1]));
                ll walk = a[i] - fly;
                if(walk) {
                    time += walk * 5;
                    stamina += walk;
                }
                if(fly) {
                    //treat like lava
                    start = 1;
                    if(stamina < fly) return -1;
                    stamina -= fly;
                    time += fly;
                }
            } else if(s[i] == 'W') {
                time += a[i] * 3;
                stamina += a[i];
                water_vis = 1;
            } else {
                if(stamina >= a[i]) {
                    stamina -= a[i];
                    time += a[i];
                } else {
                    time += a[i];
                    ll diff = a[i] - stamina;
                    stamina = 0;
                    if(start) return -1;
                    ll mult = water_vis ? 3 : 5;
                    time += diff * mult;
                }
            }
        }

        ll water_conv = stamina / 2;
        time -= water_conv * 3;
        time += water_conv;

        return time;
    };

    ll lo = 0, hi = gsuf[0];
    while(lo != hi) {
        ll m = (lo + hi + 1) / 2;
        if(check(m) != -1) {
            lo = m;
        } else {
            hi = m - 1;
        }
    }

    // cout << "lo : " << lo << endl;

    cout << check(lo) / 2 << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// /*


// 3
// 1 1 1
// WLG


// output should be 7

// */

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) {
//         cin >> x;
//         x *= 2;
//     }

//     string s; cin >> s;

//     int phase = 0; // phase 0 = only access to ground, phase 1 = access to water also
//     ll res = 0;
//     ll ground = 0, water = 0;

//     auto optimize_flight = [&]() -> void {
//         ll conv = (ground + water) / 2;
//         ll gconv = min(conv, ground);
//         ll wconv = conv - gconv;

//         res -= gconv * 5;
//         res -= wconv * 5;
//         res += conv;
//         ground = 0, water = 0;
//     };

//     for(int i = 0; i < n; i++) {
//         if(phase == 0 && s[i] == 'W') {
//             optimize_flight();
//             phase = 1;
//         }

//         if(phase == 0) {
//             if(s[i] == 'G') {
//                 res += a[i] * 5;
//                 ground += a[i];
//             } else {
//                 ll sub = min(a[i], ground);
//                 a[i] -= sub;
//                 ground -= sub;
//                 res += sub;
//                 res += a[i] * 5;
//             }
//         } else {
//             if(s[i] == 'G') {
//                 res += a[i] * 5;
//                 ground += a[i];
//             }
//         }

//         if(s[i] == 'G') {
//             if(phase == 0) {
//             } else {
//                 gt += a[i];
//                 res += a[i] * 3;
//             }
//         } else if(s[i] == 'W') {
//             if(phase == 0) {
//                 optimize_flight();
//                 phase = 1;
//             }
//             res += a[i] * 3;
//             stamina += a[i];
//         } else {
//         }
//     }

//     optimize_flight();

//     cout << res / 2 << '\n';

//     return 0;
// }
