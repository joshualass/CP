#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
10
1
-1
2 
-1 -1
3 
-1 -1 -1
4
-1 -1 -1 -1
5
-1 -1 -1 -1 -1
6
-1 -1 -1 -1 -1 -1
7
-1 -1 -1 -1 -1 -1 -1
8
-1 -1 -1 -1 -1 -1 -1 -1
9
-1 -1 -1 -1 -1 -1 -1 -1 -1
10
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1

*/

template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

//Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
template<int P>
struct Mint {
    int x;
    constexpr Mint(): x{} {}
    constexpr Mint(ll x): x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if(P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if(x < 0) {
            x += getMod();
        }
        if(x >= getMod()) { //not sure why this is needed
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Mint operator-() const {
        Mint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr Mint inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr Mint &operator*=(Mint rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr Mint &operator+=(Mint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Mint &operator-=(Mint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Mint &operator/=(Mint rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
        ll v;
        is >> v;
        a = Mint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(Mint lhs, Mint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) {
        return lhs.val() != rhs.val();
    }
};

constexpr int P = 998244353;
using Z = Mint<P>;
// using Z = double;
const int MAXN = 1e6;
Z fact[MAXN + 1], inv_fact[MAXN + 1];

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(int n = MAXN) {
    fact[0] = Z(1);
    inv_fact[0] = Z(1);
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i;
    }
    inv_fact[n] = 1 / fact[n];
    for(int i = n - 1; i >= 1; i--) {
        inv_fact[i] = inv_fact[i+1] * (i + 1);
    }
}

/*
init_fact()
*/

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    // vector<int> mxs(n + 1);
    // for(int i = 1; i <= n; i++) {
    //     mxs[i] = 8;
    // }

    // vector dp(n + 1, vector(n + 1, vector<vector<Z>>(0)));
    // for(int len = 0; len <= n; len++) {
    //     for(int l = 0; l + len <= n; l++) {
    //         int r = l + len;
    //         dp[l][r].assign(mxs[len] + 1, vector<Z>(mxs[len] + 1));
    //         if(len == 0) {
    //             dp[l][r][0][0] = 1;
    //         } else {
    //             for(int p = l; p < r; p++) {
    //                 int ladd = 0, radd = 0;
    //                 if(l && (r == n || p - l <= r - p)) {
    //                     ladd = 1;
    //                 } else if(r != n) {
    //                     radd = 1;
    //                 }
    //                 Z chooses = choose(len - 1, p - l);
    //                 // cout << "l : " << l << " r : " << r << " p : " << p << " chooses : " << chooses << '\n';
    //                 if(a[p] == -1) {
    //                     vector<Z> l_ways(dp[l][p].size()), r_ways(dp[p+1][r][0].size());
    //                     for(int i = 0; i < dp[l][p].size(); i++) {
    //                         for(int j = 0; j < dp[l][p][i].size(); j++) {
    //                             l_ways[i] += dp[l][p][i][j];
    //                         }
    //                     }
    //                     for(int i = 0; i < dp[p+1][r].size(); i++) {
    //                         for(int j = 0; j < dp[p+1][r][i].size(); j++) {
    //                             r_ways[j] += dp[p+1][r][i][j];
    //                         }
    //                     }
    //                     for(int i = 0; i < dp[l][p].size(); i++) {
    //                         for(int j = 0; j < dp[p+1][r][0].size(); j++) {
    //                             if(i + ladd < dp[l][r].size() && j + radd < dp[l][r][i + ladd].size()) {
    //                                 dp[l][r][i + ladd][j + radd] += l_ways[i] * r_ways[j] * chooses;
    //                             }
    //                         }
    //                     }
    //                 } else {
    //                     for(int i = 0; i < dp[l][p].size(); i++) {
    //                         for(int j = 0; j < dp[p+1][r][0].size(); j++) {
    //                             for(int l_contrib = 0; l_contrib <= a[p]; l_contrib++) {
    //                                 int r_contrib = a[p] - l_contrib;
    //                                 if(l_contrib < dp[l][p][0].size() && r_contrib < dp[p+1][r].size() && i + ladd < dp[l][r].size() && j + radd < dp[l][r][i].size()) {
    //                                     dp[l][r][i + ladd][j + radd] += dp[l][p][i][l_contrib] * dp[p+1][r][r_contrib][j] * chooses;
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //         // cout << "l : " << l << " r : " << r << '\n';
    //         // for(int i = 0; i < dp[l][r].size(); i++) {
    //         //     for(int j = 0; j < dp[l][r][i].size(); j++) {
    //         //         cout << dp[l][r][i][j] << " \n"[j == dp[l][r][i].size() - 1];
    //         //     }
    //         // }
    //     }
    // }

    vector dp(n + 1, vector(n + 1, vector(8, vector<Z>(8))));
    for(int len = 0; len <= n; len++) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            if(len == 0) {
                dp[l][r][0][0] = 1;
            } else {
                for(int p = l; p < r; p++) {
                    int ladd = 0, radd = 0;
                    if(l && (r == n || p - (l - 1) <= r - p)) {
                        ladd = 1;
                    } else if(r != n) {
                        radd = 1;
                    }
                    Z chooses = choose(len - 1, p - l);
                    // cout << "l : " << l << " r : " << r << " p : " << p << " chooses : " << chooses << '\n';
                    if(a[p] == -1) {
                        vector<Z> l_ways(8), r_ways(8);
                        for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                l_ways[i] += dp[l][p][i][j];
                            }
                        }
                        for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                r_ways[j] += dp[p+1][r][i][j];
                            }
                        }
                        for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                if(i + ladd < 8 && j + radd < 8) {
                                    dp[l][r][i + ladd][j + radd] += l_ways[i] * r_ways[j] * chooses;
                                }
                            }
                        }
                    } else {
                        for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                for(int l_contrib = 0; l_contrib <= a[p]; l_contrib++) {
                                    int r_contrib = a[p] - l_contrib;
                                    if(l_contrib < 8 && r_contrib < 8 && i + ladd < 8 && j + radd < 8) {
                                        dp[l][r][i + ladd][j + radd] += dp[l][p][i][l_contrib] * dp[p+1][r][r_contrib][j] * chooses;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // cout << "l : " << l << " r : " << r << '\n';
            // for(int i = 0; i < dp[l][r].size(); i++) {
            //     for(int j = 0; j < dp[l][r][i].size(); j++) {
            //         cout << dp[l][r][i][j] << " \n"[j == dp[l][r][i].size() - 1];
            //     }
            // }
        }
    }

    cout << dp[0][n][0][0] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}