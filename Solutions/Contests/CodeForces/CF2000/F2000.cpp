#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int use(vector<array<int,2>> &a, int use, int k) {
    vector<int> dp(k + 1, MOD);
    dp[0] = 0;
    for(int i = 0; i < a.size(); i++) {
        if(i != use) {
            for(int j = k; j - a[i][0] - a[i][1] >= 0; j--) {
                dp[j] = min(dp[j], dp[j - a[i][0] - a[i][1]] + a[i][0] * a[i][1]);
            }
        }
    }
    int res = dp[k];
    int ops = 0;

    array<int,2> left = a[use];
    if(left[0] > left[1]) {
        swap(left[0], left[1]);
    }
    k--;
    while(k >= 0) {
        ops += left[0];
        left[1]--;
        res = min(res, ops + dp[k]);
        k--;
        if(left[0] > left[1]) {
            swap(left[0], left[1]);
        }
        if(left[0] == 0 && left[1] == 0) {
            break;
        }
    }
    return res;
}

void solve() {

    int n, k; cin >> n >> k;
    
    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    int res = MOD;
    for(int i = 0; i < n; i++) {
        res = min(res, use(a, i, k));
    }
    cout << (res == MOD ? -1 : res) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}