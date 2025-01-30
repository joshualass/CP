#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x; cin >> n >> x;
    array<ll,3> dp = {0,0,0};
    ll res = 0;
    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        array<ll,3> ndp = {0,0,0};
        ndp[0] = max({0LL, dp[0] + a, a});
        ndp[1] = max({dp[0],dp[1],0LL}) + a * x;
        ndp[2] = max(dp[1],dp[2]) + a;
        dp = ndp;
        res = max(res, *max_element(dp.begin(),dp.end()));
    }
    cout << res << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, x; cin >> n >> x;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;

//     array<ll,3> b = {0,0,-1};

//     ll l = 0, c = 0;
//     for(int i = 0; i < n; i++) {
//         c += a[i] * x - a[i];
//         if(c < 0) {
//             c = 0;
//             l = i + 1;
//         }
//         if(c > b[0]) {
//             b = {c,l,i};
//         }
//     }

//     for(int i = b[1]; i <= b[2]; i++) {
//         a[i] *= x;
//     }

//     ll res = 0;
//     c = 0;
//     for(int i = 0; i < n; i++) {
//         c += a[i];
//         if(c < 0) {
//             c = 0;
//         }
//         res = max(res,c);
//     }

//     cout << res << '\n';

//     return 0;
// }