#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    vector<int> dp(n,0);
    for(int &x : a) cin >> x;

    int l = 1, r = 1e9;
    int length = (n - 1) % k + 1;
    while(l != r) {
        int m = (l + r + 1) / 2;
        fill(dp.begin(), dp.end(), 0);
        for(int i = 0; i < n; i++) {
            int use = (a[i] < m ? 1 : 0);
            int pos = i % k;
            if(pos == 0) {
                dp[i] = use;
                if(i - k >= 0) {
                    dp[i] = min(dp[i], dp[i - k]);
                }
            } else {
                int usemax = dp[i-1];
                if(i - k - 1 >= 0) {
                    usemax = min(usemax, dp[i - k - 1]);
                }
                dp[i] = use + usemax;
                if(i - k >= 0) {
                    dp[i] = min(dp[i], dp[i - k]);
                }
            }
        }
        // cout << "m : " << m << " dp : " << dp << '\n';
        if(dp.back() <= (length - 1) / 2) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}