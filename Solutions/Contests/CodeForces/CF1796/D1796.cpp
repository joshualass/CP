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

array<ll,2> findmaxsum(vector<ll> &a, int start, int stop) {
    array<ll,2> res = {0,0};
    ll cur = 0;
    ll lo = start;
    for(int i = start; i < stop; i++) {
        cur += a[i];
        if(cur > res[0]) {
            res = {cur, i - lo + 1};
        }
        if(cur < 0) {
            cur = 0;
            lo = i + 1;
        }
    }
    return res;
}

void solve(int tc) {

    ll n, k, x; cin >> n >> k >> x;
    vector<vector<ll>> dp(n+1, vector<ll>(k + 1)); //stores maximum range ending at index i, after using exactly k of the additions. 

    ll res = 0;

    for(int i = 1; i <= n; i++) {
        ll num; cin >> num;
        for(int j = 0; j <= k && j <= i; j++) {
            if(i != j) { //we can't use ghost values
                dp[i][j] = max({dp[i][j], dp[i-1][j] - x + num});
            }
            if(j) { //we can try doing an operation
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + x + num);
            }
            if(n - i >= k - j) {
               res = max(res, dp[i][j]);
            }
        }
    }

    // cout << "dp\n";
    // for(auto x : dp) {
    //     cout << x << "\n";
    // }

    cout << res << '\n';

    // ll n, k, x; cin >> n >> k >> x;
    // vector<ll> a(n);
    // vector<ll> p(n + 1);
    // for(int i = 0; i < n; i++) {
    //     cin >> a[i];
    //     a[i] -= x;
    //     p[i+1] = p[i] + a[i];
    // }

    // if(tc == 37) {
    //     cout << "x:" << x << '\n';
    // }

    // // cout << "a : " << a << '\n';
    // // cout << "p : " << p << '\n';

    // x = x * -2;
    // // cout << "after x : " << x << '\n';
    // if(x == 0) {
    //     cout << findmaxsum(a,0,n)[0] << '\n';
    // } else if(x < 0) {
    //     ll res = 0;
    //     for(int l = 0; l <= k; l++) {
    //         for(int i = 0; i + l <= n; i++) {
    //             res = max(res, p[i + l] - p[i] - x * l);
    //         }
    //     }
    //     array<ll,2> resm = findmaxsum(a,0,n);
    //     if(resm[1] > k) {
    //         res = max(res, resm[0] - k * x);
    //     }
    //     cout << res << '\n';
    // } else {
    //     ll res = 0;
    //     for(int start = 0; start <= k; start++) {
    //         for(int stop = n; stop >= n - k && stop > start; stop--) {
    //             int unused = start + n - stop;
    //             ll sub = 0;
    //             if(unused <= k) {
    //                 sub += x * (k - unused);
    //             }
    //             res = max(res, findmaxsum(a,start,stop)[0] - sub);
    //         }
    //     }
    //     cout << res << '\n';
    // }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        solve(i);
    }

    return 0;
}