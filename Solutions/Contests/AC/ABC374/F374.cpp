#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll dp[101][10001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, K, x; cin >> n >> K >> x;
    vector<ll> t(n);
    for(ll &x : t) cin >> x;

    vector<ll> pt(n+1);
    for(int i = 1; i <= n; i++) {
        pt[i] = pt[i-1] + t[i-1];
    }

    set<ll> s;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            s.insert(t[i] + x * j);
        }
    }

    vector<ll> times(s.begin(), s.end());
    times.insert(times.begin(), -100000000000LL);
    int m = times.size();

    vector<int> p(m);

    for(int i = 1; i < m; i++) {
        ll l = 0, r = i - 1;
        while(l != r) {
            ll m = (l + r + 1) / 2;
            if(times[m] <= times[i] - x) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        p[i] = l;
    }

    for(int i = 0; i < 101; i++) {
        fill(begin(dp[i]), end(dp[i]), (ll) 1e18);
    }

    fill(begin(dp[0]), end(dp[0]), 0LL);

    // cout << "m : " << m << '\n';
    // cout << "times : " << times << '\n';
    // cout << "pt : " << pt << '\n';
    // cout << "p : " << p << '\n';
    
    for(ll i = 1; i <= n; i++) {
        for(int j = 1; j < m; j++) {
            if(times[j] >= t[i-1]) {
                dp[i][j] = dp[i][j-1];
                for(int k = 1; k <= min(i,K); k++) {
                    ll prevti = p[j];
                    ll prevt = times[prevti];
                    dp[i][j] = min(dp[i][j], dp[i-k][prevti] + k * times[j] - (pt[i] - pt[i-k]));
                }
                // cout << "i : " << i << " j : " << j << " dp : " << dp[i][j] << '\n';
            }
        }
    }

    cout << dp[n][m - 1] << '\n';

    return 0;
}