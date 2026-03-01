#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

// //numbers are NOT a superset :)
// void solve() {
    
//     ll s, m; cin >> s >> m;
//     int p = 0;
//     for(int i = 0; i < 60; i++) {
//         if(((m >> i) & 1) == 0) break;
//         p++;
//     }    

//     ll imp = s & ((1LL << p) - 1);
//     ll os = (1LL << p) - imp;

//     auto test = [&](ll len) -> int {

//     };

// }

void solve() {
    ll s, m; cin >> s >> m;
    int f = 0;
    for(int i = 0; i < 60; i++) {
        if((m >> i) & 1) break;
        f++;
    }
    ll l = 1, r = 2e18;
    while(l != r) {
        ll mid = (l + r) / 2;
        ll cur = s;
        for(int bit = 59; bit >= 0; bit--) {
            if((m >> bit) & 1) {
                ll cnt = min(mid,(cur >> bit));
                cur -= cnt << bit;
            }
        }
        // cout << "m : " << mid << " cur : " << cur << endl;
        if(cur) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    if(l == 2e18) {
        cout << "-1\n";
    } else {
        cout << l << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}