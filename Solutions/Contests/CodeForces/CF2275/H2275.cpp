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

constexpr int P = 1e9 + 7;
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
    
    int n, m; cin >> n >> m;
    vector<vector<Z>> a(n, vector<Z>(m));
    vector<vector<Z>> p(n + 1, vector<Z>(m + 1));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x; cin >> x;
            a[i][j] = x;
        }
    }

    auto get_flags = [&](int i, int j, int k, int l) -> int {
        int ok = 1;
        if(k == 0) {
            if(i % 2) ok = 0;
        } else {
            if((n - i - 1) % 2) ok = 0;
        }
        if(l == 0) {
            if(j % 2) ok = 0;
        } else {
            if((m - j - 1) % 2) ok = 0;
        }
        return ok;
    };

    auto query = [&](int rl, int rr, int cl, int cr) -> Z {
        return p[rr][cr] - p[rl][cr] - p[rr][cl] + p[rl][cl];
    };

    Z res = 0;
    for(int k = 0; k < 2; k++) {
        for(int l = 0; l < 2; l++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    p[i+1][j+1] = 0;
                    auto flag = get_flags(i, j, k ^ 1, l ^ 1);
                    if(flag) {
                        p[i+1][j+1] = a[i][j];
                    } else {
                        p[i+1][j+1] = 0;
                    }
                }
            }

            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    p[i][j] += p[i-1][j] + p[i][j-1] - p[i-1][j-1];
                }
            }

            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    auto flag = get_flags(i, j, k, l);
                    if(flag) {
                        int rl, rr, cl, cr;
                        if(k == 0) {
                            rl = i, rr = n;
                        } else {
                            rl = 0, rr = i;
                        }
                        if(l == 0) {
                            cl = j, cr = m;
                        } else {
                            cl = 0, cr = j;
                        }
                        Z sum = query(rl, rr, cl, cr);
                        res += a[i][j] * sum;
                    }
                }
            }
        }
    }

    if((n + m) % 2) res *= -1;
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// template<typename T>
// ostream& operator<<(ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

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
// // using Z = double;
// const int MAXN = 1e6;
// Z fact[MAXN + 1], inv_fact[MAXN + 1];

// Z choose(int n, int k) {
//     if(k < 0 || k > n) return 0;
//     return fact[n] * inv_fact[k] * inv_fact[n-k];
// }

// void init_fact(int n = MAXN) {
//     fact[0] = Z(1);
//     inv_fact[0] = Z(1);
//     for(int i = 1; i <= n; i++) {
//         fact[i] = fact[i-1] * i;
//     }
//     inv_fact[n] = 1 / fact[n];
//     for(int i = n - 1; i >= 1; i--) {
//         inv_fact[i] = inv_fact[i+1] * (i + 1);
//     }
// }

// /*
// init_fact()
// */

// void solve() {
    
//     int n, m; cin >> n >> m;
//     vector p(2, vector(2, vector(n + 1, vector<Z>(m + 1))));
//     vector<vector<Z>> a(n, vector<Z>(m));

//     auto get_flags = [&](int i, int j) -> vector<vector<int>>  {
//         vector<vector<int>> res(2, vector<int>(2));
//         for(int k = 0; k < 2; k++) {
//             for(int l = 0; l < 2; l++) {
//                 int ok = 1;
//                 if(k == 0) {
//                     if(i % 2) ok = 0;
//                 } else {
//                     if((n - i - 1) % 2) ok = 0;
//                 }
//                 if(l == 0) {
//                     if(j % 2) ok = 0;
//                 } else {
//                     if((m - j - 1) % 2) ok = 0;
//                 }
//                 res[k][l] = ok;
//             }
//         }
//         return res;
//     };

//     for(int i = 0; i < n; i++) { 
//         for(int j = 0; j < m; j++) {
//             int x; cin >> x;
//             a[i][j] = x;
//             auto flags = get_flags(i, j);
//             for(int k = 0; k < 2; k++) {
//                 for(int l = 0; l < 2; l++) {
//                     if(flags[k][l]) p[k][l][i+1][j+1] += a[i][j];
//                 }
//             }
//         }
//     }

//     for(int k = 0; k < 2; k++) {
//         for(int l = 0; l < 2; l++) {
//             for(int i = 1; i <= n; i++) {
//                 for(int j = 1; j <= m; j++) {
//                     p[k][l][i][j] += p[k][l][i-1][j] + p[k][l][i][j-1] - p[k][l][i-1][j-1];
//                 }
//             }
//         }
//     }

//     auto query = [&](int k, int l, int rl, int rr, int cl, int cr) -> Z {
//         return p[k][l][rr][cr] - p[k][l][rl][cr] - p[k][l][rr][cl] + p[k][l][rl][cl];
//     };

//     Z res = 0;
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             auto flags = get_flags(i, j);
//             // cout << "i : " << i << " j : " << j << " flags : " << flags << endl;
//             for(int k = 0; k < 2; k++) {
//                 for(int l = 0; l < 2; l++) {
//                     if(flags[k][l]) {
//                         int rl, rr, cl, cr;
//                         if(k == 0) {
//                             rl = i, rr = n;
//                         } else {
//                             rl = 0, rr = i;
//                         }
//                         if(l == 0) {
//                             cl = j, cr = m;
//                         } else {
//                             cl = 0, cr = j;
//                         }
//                         Z sum = query(k ^ 1, l ^ 1, rl, rr, cl, cr);
//                         res += a[i][j] * sum;
//                     }
//                 }
//             }
//         }
//     }

//     if((n + m) % 2) res *= -1;
//     cout << res << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     for(int i = 0; i < casi; i++) {

//         solve();
//     }

//     return 0;
// }