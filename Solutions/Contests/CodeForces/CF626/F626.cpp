#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(n + 1, vector<long long>(k + 1, 0)));
    dp[0][0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int l = 0; l <= k; ++l) {
                if (dp[i][j][l] == 0) continue;

                int diff = (i > 0) ? (a[i] - a[i - 1]) * j : 0;

                // Add to existing set or create a singleton set
                if (l + diff <= k) {
                    dp[i + 1][j][l + diff] = (dp[i + 1][j][l + diff] + dp[i][j][l] * (j + 1)) % 1000000007;
                }

                // Create a new set
                if (l + diff <= k) {
                    dp[i + 1][j + 1][l + diff] = (dp[i + 1][j + 1][l + diff] + dp[i][j][l]) % 1000000007;
                }
                
                // Close a set
                if (j > 0 && l + diff <= k) {
                    dp[i + 1][j - 1][l + diff] = (dp[i + 1][j - 1][l + diff] + dp[i][j][l] * j) % 1000000007;
                }
            }
        }
    }

    long long ans = 0;
    // for (int j = 0; j <= n; ++j) {
    //     for (int l = 0; l <= k; ++l) {
    //         ans = (ans + dp[n][j][l]) % 1000000007;
    //     }
    // }
    for(int l = 0; l <= k; ++l) {
        ans = (ans + dp[n][0][l]) % 1000000007;
    }

    cout << ans << endl;

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// This problem took me a long time to solve.
// dp with states
// i - up to element i has been added to a set
// j - number of "unclosed" sets, only considering the minimum element in each set
// k - total cost. sum of maxes - sum of mins. We have to be memory efficient, so stored as sum(max) - sum(min) + a_i * j
// => store number of ways to do this
// every set must be closed at the end. 
// */

// template<class T>
// constexpr T power(T a, ll b) {
//     T res = 1;
//     for (; b; b /= 2, a *= a) {
//         if (b % 2) {
//             res *= a;
//         }
//     }
//     return res;
// }

// //Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
// template<int P>
// struct Mint {
//     int x;
//     constexpr Mint(): x{} {}
//     constexpr Mint(ll x): x{norm(x % getMod())} {}

//     static int Mod;
//     constexpr static int getMod() {
//         if(P > 0) {
//             return P;
//         } else {
//             return Mod;
//         }
//     }
//     constexpr static void setMod(int Mod_) {
//         Mod = Mod_;
//     }
//     constexpr int norm(int x) const {
//         if(x < 0) {
//             x += getMod();
//         }
//         if(x >= getMod()) { //not sure why this is needed
//             x -= getMod();
//         }
//         return x;
//     }
//     constexpr int val() const {
//         return x;
//     }
//     constexpr Mint operator-() const {
//         Mint res;
//         res.x = norm(getMod() - x);
//         return res;
//     }
//     constexpr Mint inv() const {
//         assert(x != 0);
//         return power(*this, getMod() - 2);
//     }
//     constexpr Mint &operator*=(Mint rhs) & {
//         x = 1LL * x * rhs.x % getMod();
//         return *this;
//     }
//     constexpr Mint &operator+=(Mint rhs) & {
//         x = norm(x + rhs.x);
//         return *this;
//     }
//     constexpr Mint &operator-=(Mint rhs) & {
//         x = norm(x - rhs.x);
//         return *this;
//     }
//     constexpr Mint &operator/=(Mint rhs) & {
//         return *this *= rhs.inv();
//     }
//     friend constexpr Mint operator*(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res *= rhs;
//         return res;
//     }
//     friend constexpr Mint operator+(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res += rhs;
//         return res;
//     }
//     friend constexpr Mint operator-(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res -= rhs;
//         return res;
//     }
//     friend constexpr Mint operator/(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res /= rhs;
//         return res;
//     }
//     friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
//         ll v;
//         is >> v;
//         a = Mint(v);
//         return is;
//     }
//     friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
//         return os << a.val();
//     }
//     friend constexpr bool operator==(Mint lhs, Mint rhs) {
//         return lhs.val() == rhs.val();
//     }
//     friend constexpr bool operator!=(Mint lhs, Mint rhs) {
//         return lhs.val() != rhs.val();
//     }
// };

// constexpr int P = 1e9 + 7;
// using Z = Mint<P>;

// vector<Z> fact(1,1);
// vector<Z> inv_fact(1,1);

// Z choose(int n, int k) {
//     if(k < 0 || k > n) return 0;
//     while(fact.size() < n + 1) {
//         fact.push_back(fact.back() * fact.size());
//         inv_fact.push_back(1 / fact.back());
//     }
//     return fact[n] * inv_fact[k] * inv_fact[n-k];
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, K; cin >> n >> K;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     sort(a.begin(), a.end());
//     vector<vector<Z>> dp(n / 2 + 1, vector<Z>(K + 1)), next(n / 2 + 1, vector<Z>(K + 1));

//     dp[0][0] = 1;
//     int p = 0;
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n / 2 + 1; j++) {
//             for(int k = 0; k < K + 1; k++) {
//                 next[j][k] = 0;
//             }
//         }
//         for(int j = 0; j < n / 2 + 1; j++) {
//             for(int k = 0; k < K + 1; k++) {
//                 int diff = (a[i] - p) * j;
//                 if(k + diff < K + 1) {
//                     //create a new set 
//                     if(j + 1 < n / 2 + 1) {
//                         next[j+1][k + diff] += dp[j][k];
//                     }
//                     //add to existing set/create a singleton
//                     next[j][k + diff] += dp[j][k] * (j + 1);
//                     //close a set
//                     if(j) {
//                         next[j-1][k + diff] += dp[j][k] * j;
//                     }
//                 }
//             }
//         }
//         swap(dp, next);
//         p = a[i];
//     }

//     Z res = 0;
//     for(int i = 0; i < K + 1; i++) {
//         res += dp[0][i];
//     }

//     cout << res << '\n';

//     return 0;
// }