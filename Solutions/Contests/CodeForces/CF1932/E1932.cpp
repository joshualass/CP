#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    string ans = "";
    ll carry = 0;
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        sum += s[i] - '0';
    }
    for(int i = n - 1; i >= 0; i--) {
        carry += sum;
        sum -= (s[i] - '0');
        ans.push_back(carry % 10 + '0');
        carry /= 10;
    }
    while(carry) {
        ans.push_back(carry % 10 + '0');
        carry /= 10;
    }
    while(ans.back() == '0') ans.pop_back();
    reverse(ans.begin(),ans.end());
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}