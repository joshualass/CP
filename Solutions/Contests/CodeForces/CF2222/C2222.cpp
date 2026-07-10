#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    auto b = a;
    sort(b.begin(), b.end());
    int med = b[n / 2];

    vector<int> up(n + 1), ap(n + 1);

    for(int i = 0; i < n; i++) {
        up[i + 1] = up[i];
        ap[i + 1] = ap[i];
        up[i + 1] += a[i] < med;
        ap[i + 1] += a[i] > med;
    }

    // cout << "up : " << up << endl;
    // cout << "ap : " << ap << endl;

    vector<int> dp(n + 1, -inf);
    
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int len = 1; len <= i; len += 2) {
            if(up[i] - up[i - len] <= len / 2 && ap[i] - ap[i - len] <= len / 2) {
                dp[i] = max(dp[i], dp[i - len] + 1);
            }
        }
    }

    // cout << "dp : " << dp << endl;

    cout << dp[n] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}