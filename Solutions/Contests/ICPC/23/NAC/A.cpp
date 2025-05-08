#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll inf = ((ll) 1e18) + 5;

void solve() {

    ll n, d; cin >> n >> d;

    auto opow = [&](ll a, ll b) -> ll {
        ll res = 1;
        for(int i = 0; i < b; i++) {
            if(inf / a < res) res = inf;
            else res *= a;
        }
        return res;
    };

    ll s = 0;
    while(opow(d + 1, s) < n) s++;
    cout << s << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include<bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// typedef pair<int, int> pii;
// typedef vector<int> vi;
// typedef vector<vi> vvi;
// typedef vector<ll> vl;
// typedef __int128 lll;

// #define rep(i, a, b) for(int i = 0; i < (b); i++)
// #define all(x) begin(x), end(x)
// #define sz(x) (int) (x).size()

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL), cout.tie(NULL);

//     const int N = 1e6 + 1000;
//     vector<vector<lll>> dp(N + 1);
//     for(int i = 1; i <= N; i++){
//         cout << "I : " << i << endl;
//         dp[i] = vector<lll>(1, 0);
//         for(int j = 1; j <= N; j++){
//             if(i == 1) dp[i].push_back(j + 1);
//             else if(j == 1) dp[i].push_back(i + 1);
//             else {
//                 // ll nxt = dp[i - 1][j - 1] * (ll) i + dp[i][j - 1];
//                 // if(nxt < dp[])
//                 dp[i].push_back(dp[i - 1][j - 1] * (lll) i + dp[i][j - 1]);
//                 // dp[i][j] = dp[i - 1][j - 1] * i + dp[i][j - 1];
//             }
//             // cout << "PREV : " << dp[i][dp[i].size() - 1] << endl;
//             if(dp[i][dp[i].size() - 1] > (lll) 1e18) {
//                 cout << "DONE : " << j << " " << (ll) dp[i][dp[i].size() - 1] << endl;
//                 dp[i].pop_back();
//                 break;
//             }
//         }
//     }
//     cout << "DONE PRECALC" << endl;

//     int t;
//     cin >> t;
//     while(t--){
//         ll n, d;
//         cin >> n >> d;
//         if(n == 1) {
//             cout << "0\n";
//             continue;
//         }
//         ll ans = -1;
//         if(d == 1){
//             ans = n - 1;
//         }
//         else if(d == 2){
//             ll low = 1, high = 1e9 + 1000;
//             ans = high;
//             while(low <= high) {
//                 ll mid = low + (high - low) / 2;
//                 ll mxamt = (mid + 1) + mid * mid;
//                 if(mid >= n) ans = mid, high = mid - 1;
//                 else low = mid + 1;
//             }
//         }
//         else {
//             ll low = 1, high = N;
//             ans = N;
//             while(low <= high) {
//                 ll mid = low + (high - low) / 2;
//                 if(dp[d].size() <= mid || dp[d][mid] >= n) ans = mid, high = mid - 1;
//                 else low = mid + 1;
//             }
//         }
//         cout << ans << "\n";
//     }

//     return 0;
// }