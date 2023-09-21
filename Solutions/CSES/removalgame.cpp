// #pragma GCC optimize("unroll-loops,02,no-stack-protector")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int N = 5000;
ll dp[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<ll> v(n);
    for(auto &x :v)cin >> x;
    for(int i = 0; i < N; i++) {
        fill(begin(dp[i]),begin(dp[i])+N,0LL);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j + i < n; j++) {
            int l = j, r = i + j;
            if((n - (r - l)) & 1) {//player 1's turn
                if(l == r) {
                    dp[l][r] = v[l];
                } else {
                    dp[l][r] = max(dp[l+1][r] + v[l], dp[l][r-1] + v[r]);
                }
            } else {//player 2's turn
                if(l != r) {
                    dp[l][r] = min(dp[l+1][r],dp[l][r-1]);
                }
            }
        }
    }
    cout << dp[0][n-1] << "\n";
    return 0;
}