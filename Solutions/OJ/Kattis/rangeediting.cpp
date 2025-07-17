#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int solve(int n, vector<int> a) {
    a.insert(a.begin(), 0);
    n++;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));
    for(int len = 0; len <= n; len++) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            if(len == 0) {
                dp[l][r] = 0;
            } else {
                dp[l][r] = 1 + dp[l+1][r];
                for(int i = l + 1; i < r; i++) {
                    if(a[i] == a[l]) {
                        dp[l][r] = min(dp[l][r], dp[l+1][i] + dp[i][r]);
                    }
                }
            }
        }
    }
    return dp[0][n] - 1;
}

vector<int> gen_rand(int n, int seg) {
    vector<int> a(n);
    for(int i = 0; i < seg; i++) {
        int l = rng() % n, r = rng() % n;
        if(l > r) swap(l, r);
        int val = rng() % 1'000'000'001;
        for(int j = l; j <= r; j++) {
            a[j] = val;
        }
    }
    return a;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int n = 1; n <= 20; n++) {
    //     for(int segs = 1; segs <= n; segs++) {
    //         for(int cnt = 0; cnt < 20; cnt++) {
    //             vector<int> a = gen_rand(n, segs);
    //             int soln = solve(n, a);
    //             if(soln > segs) {
    //                 cout << "BAD\n";
    //                 cout << "n : " << n << " segs : " << segs << '\n';
    //                 cout << "a : " << a << '\n';
    //                 return 0;
    //             }
    //         }
    //     }
    // }

    // cout << "all tests ok!\n";

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    a.insert(a.begin(), 0);
    n++;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));
    for(int len = 0; len <= n; len++) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            if(len == 0) {
                dp[l][r] = 0;
            } else {
                dp[l][r] = 1 + dp[l+1][r];
                for(int i = l + 1; i < r; i++) {
                    if(a[i] == a[l]) {
                        dp[l][r] = min(dp[l][r], dp[l+1][i] + dp[i][r]);
                    }
                }
            }
        }
    }

    cout << dp[0][n] - 1 << '\n';

    return 0;
}
