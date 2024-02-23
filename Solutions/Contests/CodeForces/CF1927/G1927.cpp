#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<int> dp(n,MOD); //let dp[i] represent the minimum number of paint charges needed to cover all cells up to i
    for(int i = 0; i < n; i++) {
        int charge; cin >> charge;
        //use right
        int min_prev = MOD;
        if(i == 0) {
            min_prev = 0;
        } else {
            for(int j = i - 1; j < n; j++) {
                min_prev = min(min_prev,dp[j]);
            }
        }
        for(int j = 0; j < charge && i + j < n; j++) {
            dp[i+j] = min(dp[i+j],min_prev+1);
        }
        //use left
        for(int j = max(0,i-charge); j < n; j++) {
            dp[i] = min(dp[i],dp[j]+1);
        }
    }
    cout << "dp : " << dp << '\n';
    cout << dp.back() << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}