//Consider being a little bit better. 

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve() {

//     int n, x; cin >> n >> x;
//     vector<int> a(n);
//     for(int &y: a) cin >> y;

//     vector<vector<int>> pc(n,vector<int>(x,-1));
//     vector<vector<int>> pc2(n, vector<int>(x, n));

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < x; j++) {
//             if(i) {
//                 pc[i][j] = pc[i-1][j];
//             }
//         }
//         pc[i][a[i]-1] = i;
//     }

//     for(int i = n - 1; i >= 0; i--) {
//         for(int j = 0; j < x; j++) {
//             if(i != n - 1) {
//                 pc2[i][j] = pc2[i+1][j];
//             }
//         }
//         pc2[i][a[i]-1] = i;
//     }

//     vector<vector<vector<int>>> dp(n,vector<vector<int>>(n,vector<int>(x,100)));
//     vector<vector<vector<array<int,2>>>> toptwo(n,vector<vector<array<int,2>>>(n, vector<array<int,2>>(2, {100,-1})));

//     for(int length = 1; length <= n; length++) {
//         for(int l = 0; l + length <= n; l++) {
//             for(int c = 0; c < x; c++) {

//                 //handle length 1
//                 if(length == 1 && a[l] - 1 == c) {
//                     dp[l][l + length - 1][c] = 0;
//                 }

//                 //can do in 1 op if none = c.
//                 if(pc[l + length - 1][c] < l) {
//                     dp[l][l + length - 1][c] = min(dp[l][l + length - 1][c], 1);
//                 }

//                 //split array in half 
//                 for(int m = l + 1; m < l + length; m++) {

//                     dp[l][l + length - 1][c] = min(dp[l][l + length - 1][c], dp[l][m-1][c] + dp[m][l + length - 1][c]);

//                     int lo1 = 100, lo2 = 100;
//                     for(int k = 0; k < 2; k++) {
//                         if(toptwo[l][m-1][k][1] != c) {
//                             lo1 = min(lo1, toptwo[l][m-1][k][0]);
//                         }
//                         if(toptwo[m][l + length - 1][k][1] != c) {
//                             lo2 = min(lo2, toptwo[m][l + length - 1][k][0]);
//                         }
//                     }
//                     dp[l][l + length - 1][c] = min(dp[l][l + length - 1][c], lo1 + lo2 + 1);

//                 }

//                 for(int k = 0; k < 2; k++) {
//                     if(pc[l + length - 1][c] >= pc2[l][c] && toptwo[pc2[l][c]][pc[l + length - 1][c]][k][1] != c) {
//                         dp[l][l + length - 1][c] = min(dp[l][l + length - 1][c], 1 + toptwo[pc2[l][c]][pc[l + length - 1][c]][k][0]);
//                     }
//                 }

//                 if(a[l] - 1 == c && length >= 2) {
//                     dp[l][l + length - 1][c] = min(dp[l][l + length - 1][c], dp[l + 1][l + length - 1][c]);
//                 }
//                 if(a[l + length - 1] - 1 == c && length >= 2) {
//                     dp[l][l + length - 1][c] = min(dp[l][l + length - 1][c], dp[l][l + length - 2][c]);
//                 }

//                 if(toptwo[l][l + length - 1][0][0] > toptwo[l][l + length - 1][1][0]) {
//                     if(dp[l][l + length - 1][c] < toptwo[l][l + length - 1][0][0]) {
//                         toptwo[l][l + length - 1][0] = {dp[l][l + length - 1][c], c};
//                     }
//                 } else {
//                     if(dp[l][l + length - 1][c] < toptwo[l][l + length - 1][1][0]) {
//                         toptwo[l][l + length - 1][1] = {dp[l][l + length - 1][c], c};
//                     }
//                 }

//             }
//         }
//     }

//     int res = 100;
//     for(int c = 0; c < x; c++) {
//         res = min(res, dp[0][n-1][c]);
//     }

//     cout << res << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }