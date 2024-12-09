#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    int n, k;
    long long m;
    cin >> n >> m >> k;

    vector<vector<long long>> C(n + 1, vector<long long>(n + 1));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0 || j == i) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    vector<long long> dp(k + 1, 0);
    vector<long long> prev_dp(k + 1, 0);
    prev_dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        long long cnt = m / n + (i < m % n);
        vector<long long> powers(n + 1);
        for(int j = 0; j <= n; ++j) {
            powers[j] = power(C[n][j], cnt);
        }

        fill(dp.begin(), dp.end(), 0);

        for (int sum = 0; sum <= k; ++sum) {
            for (int j = 0; j <= n; ++j) {
                int new_sum = sum + j;
                if (i == n - 1 && new_sum != k) continue;
                if (new_sum <= k) {
                    dp[new_sum] = (dp[new_sum] + (prev_dp[sum] * powers[j]) % MOD) % MOD;
                }
            }
        }
        prev_dp = dp;
    }

    cout << dp[k] << endl;

    return 0;
}

// #include <iostream>
// #include <vector>

// using namespace std;
// constexpr long long MOD = 1e9 + 7;

// long long power(long long base, long long exp) {
//     long long res = 1;
//     base %= MOD;
//     while (exp > 0) {
//         if (exp % 2 == 1) res = (res * base) % MOD;
//         base = (base * base) % MOD;
//         exp /= 2;
//     }
//     return res;
// }

// int main() {
//     int n, k;
//     long long m;
//     cin >> n >> m >> k;

//     vector<vector<long long>> C(n + 1, vector<long long>(n + 1));
//     for (int i = 0; i <= n; ++i) {
//         for (int j = 0; j <= i; ++j) {
//             if (j == 0 || j == i) C[i][j] = 1;
//             else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
//         }
//     }

//     vector<long long> dp(k + 1);
//     dp[0] = 1;

//     for (int i = 0; i < n; ++i) {
//         long long cnt = m / n + (i < m % n);
//         vector<long long> next(k+1);
//         for (int sum = 0; sum <= k; ++sum) {
//             for (int j = 0; j <= n; ++j) {
//                 int new_sum = sum + j;
//                 if (i == n - 1 && new_sum != k) continue;
//                 if (new_sum <= k) {
//                     next[new_sum] = (next[new_sum] + (dp[sum] * power(C[n][j], cnt))) % MOD;
//                 }
//             }
//         }
//         swap(dp, next);
//     }

//     cout << dp[k] << endl;

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

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

//     ll n, m, k; cin >> n >> m >> k;
//     vector<Z> a(k+1);

//     a[k] = 1;

//     for(int i = 0; i < n; i++) {
//         vector<Z> next(k+1);
//         for(int j = 0; j <= n; j++) {
//             Z mul = power<Z>(choose(n,j), (m + (n - 1 - i)) / n);
//             for(int l = k; l - j >= 0; l--) {
//                 next[l-j] += a[l] * mul;
//             }
//         }
//         swap(a,next);
//     }

//     cout << a[0] << '\n';

//     return 0;
// }