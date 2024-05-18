#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;

    vector<vector<int>> mat(n + 1,vector<int>(n + 1));
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            cin >> mat[i][j];
            // mat[j][i] = mat[i][j];
        }
    }

    vector<vector<int>> dp(n);
    for(int i = 0; i < n; i++) {
        priority_queue<array<int,3>> pq;
        for(int stop = -1; stop <= i; stop++) {
            int val = mat[stop + 1][i];
            // val currently stores the beauty of the painted segment
            int idx = 0;
            if(stop - 1 >= 0) {
                val += dp[stop - 1].back();
                idx = dp[stop - 1].size() - 1;
            }
            pq.push({val,stop,idx});
        }
        while(pq.size() && dp[i].size() != k) {
            array<int,3> a = pq.top();
            pq.pop();
            dp[i].push_back(a[0]);
            if(a[2] != 0) {
                int idx = a[2] - 1;
                int val = mat[a[1] + 1][i] + dp[a[1] - 1][idx];
                pq.push({val,a[1],idx});
            }
        }
        reverse(dp[i].begin(), dp[i].end());
    }

    for(int i = k - 1; i >= 0; i--) {
        cout << dp[n-1][i] << " \n"[i == 0];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}