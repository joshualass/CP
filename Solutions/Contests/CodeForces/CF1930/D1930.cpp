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
    string s; cin >> s;
    vector<bool> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = s[i] - '0';
    }

    vector<ll> dp(n);

    for(int i = 0; i < n; i++) {
        if(i == 0) {
            dp[i] = v[0];
        } else if(i == 1) {
            dp[i] = max(v[0] * 1, v[1] * 2);
        } else if(i == 2) {
            dp[i] = max({v[0] * 1, v[1] * 2, v[2] * 3});
        } else {
            if(v[i]) {
                dp[i] = (i + 1) + min({dp[i-3],dp[i-2],dp[i-1]});
            } else {
                dp[i] = dp[i-1];
            }
        }
    }
    cout << reduce(dp.begin(), dp.end()) << '\n';
    
    // solves inverse of this problem :( oops
    // int n; cin >> n;
    // string s; cin >> s;
    // vector<bool> v(n);
    // for(int i = 0; i < n; i++) {
    //     v[i] = s[i] - '0';
    // }
    // vector<int> min_lefts(n);
    // for(int i = 0; i < n; i++) {
    //     int j = i;
    //     min_lefts[i] = i;
    //     while(v[j] != 1 && j >= 0) {
    //         j = min_lefts[j] - 1;
    //     }
    //     min_lefts[i] = j;
    // }
    // // cout << "min_lefts : " << min_lefts << '\n';
    // vector<int> min_rights(n);
    // for(int i = n - 1; i >= 0; i--) {
    //     int j = i;
    //     min_rights[i] = i;
    //     while(v[j] != 1 && j < n) {
    //         j = min_rights[j] + 1;
    //     }
    //     min_rights[i] = j;
    // }
    // // cout << "rights : " << min_rights << '\n';
    // ll ans = 0;

    // for(int i = 0; i < n; i++) {
    //     ll val = 0;
    //     if(min_lefts[i] >= 0) {
    //         ll before = min_lefts[i] + 1;
    //         ll after = n - i;
    //         val += before * after;
    //     }
    //     if(min_rights[i] < n) {
    //         ll before = i + 1;
    //         ll after = n - min_rights[i];
    //         val += before * after;
    //     }
    //     if(min_lefts[i] >= 0 && min_rights[i] < n) {
    //         ll before = min_lefts[i] + 1;
    //         ll after = n - min_rights[i];
    //         val -= before * after;
    //     }
    //     // cout << "i : " << i << " val : " << val << '\n';
    //     ans += val;
    // }
    // cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}