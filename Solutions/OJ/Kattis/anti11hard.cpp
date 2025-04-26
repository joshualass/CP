#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const ll mod = 1e9 + 7;

/*
init_fact()
*/

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    auto get_best = [&](string t) -> int {
        int best = 0;
        for(int j = t.size() - 1; j >= 0; j--) {
            if(t.substr(j) == s.substr(0, t.size() - j)) {
                best = t.size() - j;
            }
        }
        if(best == s.size()) best = -1; 
        return best;
    };

    vector<array<int,2>> pc(s.size());
    for(int i = 0; i < s.size(); i++) {
        string t = s.substr(0, i);
        pc[i][0] = get_best(t + "0");
        pc[i][1] = get_best(t + "1");
    }

    // cout << "s : " << s << '\n';
    // cout << "pc : " << pc << "\n";

    vector<vector<int>> dp(n + 1, vector<int>(s.size()));
    dp[0][0] = 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < s.size(); j++) {
            for(int k = 0; k < 2; k++) {
                if(pc[j][k] != -1) {
                    dp[i+1][pc[j][k]] += dp[i][j];
                    if(dp[i+1][pc[j][k]] >= mod) dp[i+1][pc[j][k]] -= mod;
                }
            }
        }
    }

    ll res = 0;
    for(int i = 0; i < s.size(); i++) {
        res += dp[n][i];
    }

    cout << res % mod << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1'000'000'007;
// //need to optimize with kmp
// void solve() {
//     int n; cin >> n;
//     string b; cin >> b;
//     // string b = "11";

//     if(b.size() == 1) {
//         cout << "1\n";
//         return;
//     }

//     ll allergic = 0;
//     for(int i = 0; i < b.size(); i++) {
//         allergic <<= 1;
//         allergic += b[i] - '0';
//     }

//     vector<vector<ll>> dp(n, vector<ll>(1 << b.size()));
//     dp[0][0] = 1;
//     dp[0][1] = 1;
//     //always use pull-dp
//     for(int i = 1; i < n; i++) {
//         for(int bm = 0; bm < 1 << b.size(); bm++) {
//             if(bm != allergic) {
//                 int prev1 = (bm >> 1);
//                 int prev2 = (bm >> 1) + (1 << (b.size() - 1));
//                 dp[i][bm] += dp[i-1][prev1];
//                 dp[i][bm] += dp[i-1][prev2];
//                 dp[i][bm] %= MOD;
//             }
//         }
//     }
//     ll res = 0;
//     for(int i = 0; i < 1 << b.size(); i++) {
//         res += dp[n-1][i];
//     }
//     cout << res % MOD << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }