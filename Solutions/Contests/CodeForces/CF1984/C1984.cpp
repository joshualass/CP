// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve() {
//     int n; cin >> n;
//     ll lo = 0, hi = 0;
//     for(int i = 0; i < n; i++) {
//         ll num; cin >> num;
//         hi = max(hi + num, abs(lo + num));
//         lo += num;
//     }
//     cout << max(hi, abs(lo)) << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    map<ll,ll> bruh;
    ll lo = 0, hi = 0;
    ll loway = 1, hiway = 1;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        bruh.clear();
        bruh[lo+num] += loway;
        bruh[abs(lo+num)] += loway;
        if(lo != hi) {
            bruh[hi+num] += hiway;
            bruh[abs(hi+num)] += hiway;
        }
        pair<ll,ll> p = *bruh.begin();
        lo = p.first, loway = p.second;
        p = (*--bruh.end());
        hi = p.first, hiway = p.second;
        loway %= MOD;
        hiway %= MOD;
    }
    cout << hiway % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}