#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x: v) cin >> x;
    vector<int> dp(n,INT_MAX);
    dp.push_back(0);
    for(int i = n - 1; i >= 0; i--) {
        if(v[i] + i < n) {
            dp[i] = dp[v[i] + i + 1];
        }
        dp[i] = min(dp[i], dp[i+1] + 1);
    }
    // cout << dp << "\n";
    cout << dp[0] << "\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}