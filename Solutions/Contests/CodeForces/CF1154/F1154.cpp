#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());
    n = k;
    a.resize(n);

    vector<ll> p(n + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = a[i-1] + p[i-1];
    }

    vector<int> b(n + 1);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        if(x <= n) {
            b[x] = max(b[x], y);
        }
    }

    vector<ll> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = LLONG_MAX;
        for(int j = 1; j <= i; j++) {
            dp[i] = min(dp[i], dp[i - j] + p[i] - p[i - j] - (p[i - j + b[j]] - p[i - j]));
        }
    }

    // cout << "a : " << a << endl;
    // cout << "p : " << p << endl;
    // cout << "dp : " << dp << endl;

    cout << dp[n] << '\n';

    return 0;
}
