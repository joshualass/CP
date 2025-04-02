#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x, x--;
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 1e18)); //dp[i][j] => minimum operations that need to be done before index i in order to fully remove this interval, this does not depend on dp0
    vector<vector<ll>> dp0(n + 1, vector<ll>(n + 1)); //dp0[i][j] => maximum number of operations to be done on this range, has no deps. 

    for(ll len = 0; len <= n; len++) {
        for(ll l = 0; l + len <= n; l++) {
            ll r = l + len;
            if(len % 2 == 0) {
                if(len == 0) {
                    dp[l][r] = 0;
                } else {
                    if(a[l] <= l && (l - a[l]) % 2 == 0) {
                        ll need = (l - a[l]) / 2;
                        if(need >= dp[l+1][r-1]) {
                            dp[l][r] = min(dp[l][r], need);
                        }
                    }
                    for(ll m = l + 2; m < r; m += 2) {
                        dp[l][r] = min(dp[l][r], max(dp[l][m], dp[m][r] - (m - l) / 2));
                    }
                }
            }

            for(ll m = l; m <= r; m++) {
                if(dp0[l][m] >= dp[m][r]) {
                    dp0[l][r] = max(dp0[l][r], dp0[l][m] + (r - m) / 2);
                }
                dp0[l][r] = max(dp0[l][r], dp0[l][m] + dp0[m][r]);
            }
        }
    }    

    cout << dp0[0][n] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}


//dp[i][j] => is it possible to remove all the elements on this interval given that previous interval is untouched


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// /*

// 6
// 1 2 1 10 10 10

// */

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
//     for(auto x : adj) {
//         for(auto y : x) os << y << " ";
//         os << "\n";
//     }
//     return os;
// }

// void solve() {
//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) {
//         cin >> x;
//         x--;    
//     }

//     vector<vector<bool>> poss(n, vector<bool>(n));
//     vector<int> dp(n);

//     for(int hi = 1; hi < n; hi++) {
//         for(int lo = hi - 1; lo >= 0; lo--) {
//             for(int i = lo + 1; i + 1 < hi; i++) {
//                 poss[lo][hi] = poss[lo][hi] || (poss[lo][i] && poss[i+1][hi]);
//             }
//             bool hit = 0;
//             int mb = lo == 0 ? lo : dp[lo-1];
//             for(int i = 0; i <= mb; i += 2) {
//                 if(a[lo] == lo - i) hit = 1;
//             }
//             if(hit && (poss[lo+1][hi-1] || hi - lo == 1)) {
//                 poss[lo][hi] = 1;
//             }
//             if(poss[lo][hi]) {
//                 cout << "poss : " << lo << ", " << hi << '\n';
//                 for(int i = hi; i < n; i++) {
//                     dp[i] = max(dp[i], mb + hi - lo + 1);
//                 }
//             }
//         }
//     }



//     cout << "poss\n" << poss;

//     cout << (*max_element(dp.begin(), dp.end()) >> 1) << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }