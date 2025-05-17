#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {

    ll n; cin >> n;

    cout << "mul 999999999" << endl;
    int _; cin >> _;

    cout << "digit" << endl;
    cin >> _;

    if(n != 81) {
        cout << "add " << n - 81 << endl;
        cin >> _;
    }

    cout << "!" << endl;
    cin >> _;

}

// void solve() {
    
//     ll n; cin >> n;

//     cout << "mul " << 9 << endl;
//     int _; cin >> _;

//     cout << "digit" << endl;
//     cin >> _;
//     cout << "digit" << endl;
//     cin >> _;

//     if(n != 9) {
//         cout << "add " << n - 9 << endl;
//         cin >> _;
//     }
    
//     cout << "!" << endl;
//     cin >> _;
// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // auto S = [&](ll x) -> int {
    //     string s = to_string(x);
    //     ll res = 0;
    //     for(char c : s) res += c - '0';
    //     return res;
    // };

    // ll best = INT_MAX, y = -1;

    // for(int i = 1; i <= 1000000; i++) {
    //     int hi = 0;
    //     for(int j = 1; j <= 81; j++) {
    //         hi = max(hi, S(j + i));
    //     }
    //     if(hi < best) {
    //         best = hi;
    //         y = i;
    //     }
    // }

    // cout << "best : " << best << " y : " << y << '\n';

    // int m = 0;    

    // for(int i = 1; i <= 1000000000; i++) {
    //     m = max(m, S(3LL * i));
    // }

    // cout << m << '\n';

    // for(ll i = 999999999; i <= 1000000000000; i += 999999999) cout << i << '\n';

    // cout << 999999999LL * 999999999LL << '\n';

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}