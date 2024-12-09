#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    vector<vector<long long> > dp(n + 1, vector<long long>(n + 1, 0));

    for (int i = 0; i <= n; ++i) {
        dp[i][i] = 1;
    }

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l <= n - len; ++l) {
            int r = l + len;
            for (int k = l; k < r; ++k) {
                if (k == r - 1 || b[k + 1] >= b[l]) {
                    dp[l][r] = (dp[l][r] + (dp[l + 1][k + 1] * dp[k + 1][r])) % 1000000007;
                }
            }
        }
    }

    cout << dp[1][n] << endl; // Corrected output

    return 0;
}

// #include <iostream>
// #include <vector>

// using namespace std;

// int main() {
//     int n;
//     cin >> n;

//     vector<int> b(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> b[i];
//     }

//     vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));

//     for (int i = 0; i <= n; ++i) {
//         dp[i][i] = 1;
//     }

//     for (int len = 1; len <= n; ++len) {
//         for (int l = 0; l <= n - len; ++l) {
//             int r = l + len;
//             for (int k = l; k < r; ++k) {
//                 if (k == r - 1 || b[k + 1] >= b[l]) {
//                     dp[l][r] = (dp[l][r] + (dp[l + 1][k + 1] * dp[k + 1][r])) % 1000000007;
//                 }
//             }
//         }
//     }

//     cout << dp[1][n] << endl;

//     return 0;
// }

// // #include <bits/stdc++.h>
// // typedef long long ll;
// // typedef long double ld;
// // using namespace std;

// // template<class T>
// // constexpr T power(T a, ll b) {
// //     T res = 1;
// //     for (; b; b /= 2, a *= a) {
// //         if (b % 2) {
// //             res *= a;
// //         }
// //     }
// //     return res;
// // }

// // //Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
// // template<int P>
// // struct Mint {
// //     int x;
// //     constexpr Mint(): x{} {}
// //     constexpr Mint(ll x): x{norm(x % getMod())} {}

// //     static int Mod;
// //     constexpr static int getMod() {
// //         if(P > 0) {
// //             return P;
// //         } else {
// //             return Mod;
// //         }
// //     }
// //     constexpr static void setMod(int Mod_) {
// //         Mod = Mod_;
// //     }
// //     constexpr int norm(int x) const {
// //         if(x < 0) {
// //             x += getMod();
// //         }
// //         if(x >= getMod()) { //not sure why this is needed
// //             x -= getMod();
// //         }
// //         return x;
// //     }
// //     constexpr int val() const {
// //         return x;
// //     }
// //     constexpr Mint operator-() const {
// //         Mint res;
// //         res.x = norm(getMod() - x);
// //         return res;
// //     }
// //     constexpr Mint inv() const {
// //         assert(x != 0);
// //         return power(*this, getMod() - 2);
// //     }
// //     constexpr Mint &operator*=(Mint rhs) & {
// //         x = 1LL * x * rhs.x % getMod();
// //         return *this;
// //     }
// //     constexpr Mint &operator+=(Mint rhs) & {
// //         x = norm(x + rhs.x);
// //         return *this;
// //     }
// //     constexpr Mint &operator-=(Mint rhs) & {
// //         x = norm(x - rhs.x);
// //         return *this;
// //     }
// //     constexpr Mint &operator/=(Mint rhs) & {
// //         return *this *= rhs.inv();
// //     }
// //     friend constexpr Mint operator*(Mint lhs, Mint rhs) {
// //         Mint res = lhs;
// //         res *= rhs;
// //         return res;
// //     }
// //     friend constexpr Mint operator+(Mint lhs, Mint rhs) {
// //         Mint res = lhs;
// //         res += rhs;
// //         return res;
// //     }
// //     friend constexpr Mint operator-(Mint lhs, Mint rhs) {
// //         Mint res = lhs;
// //         res -= rhs;
// //         return res;
// //     }
// //     friend constexpr Mint operator/(Mint lhs, Mint rhs) {
// //         Mint res = lhs;
// //         res /= rhs;
// //         return res;
// //     }
// //     friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
// //         ll v;
// //         is >> v;
// //         a = Mint(v);
// //         return is;
// //     }
// //     friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
// //         return os << a.val();
// //     }
// //     friend constexpr bool operator==(Mint lhs, Mint rhs) {
// //         return lhs.val() == rhs.val();
// //     }
// //     friend constexpr bool operator!=(Mint lhs, Mint rhs) {
// //         return lhs.val() != rhs.val();
// //     }
// // };

// // constexpr int P = 1e9 + 7;
// // using Z = Mint<P>;

// // signed main() {
// //     ios_base::sync_with_stdio(false);
// //     cin.tie(NULL);

// //     int n; cin >> n;
// //     vector<int> a(n);
// //     for(int &x : a) cin >> x;
// //     vector<vector<Z>> dp(n+1,vector<Z>(n+1));
// //     for(int i = 0; i <= n; i++) {
// //         dp[i][i] = 1;
// //     }
// //     for(int le = 1; le <= n; le++) {
// //         for(int i = 0; i + le <= n; i++) {
// //             for(int j = 1; j <= le; j++) {
// //                 if(j == le || a[i+j] >= a[i]) {
// //                     dp[i][i+le] += dp[i+1][i+j] * dp[i+j][i+le];
// //                 }
// //             }
// //         }   
// //     }
// //     cout << dp[1][n] << '\n';
// //     return 0;
// // }