#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
const int MAXN = 1e5;
Z fact[MAXN + 1], inv_fact[MAXN + 1];
Z z[MAXN + 1], iz[MAXN + 1];

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(int n = MAXN) {
    fact[0] = Z(1);
    inv_fact[0] = Z(1);
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i;
        z[i] = i;
        iz[i] = 1 / z[i];
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
    
    int n, m, q; cin >> n >> m >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    map<int,vector<array<int,2>>> g;
    vector<array<int,2>> ops(q); //{slider idx, position moved to}
    for(auto &x : ops) {
        cin >> x[0] >> x[1];
        x[0]--;
        g[x[1] - x[0]].push_back(x);
    }

    vector<vector<array<int,2>>> ttfang;
    for(auto [k, v] : g) ttfang.push_back(v);

    auto get_p = [&](int i, int end, int left, int right, int lc, int rc, int ac, int neutral) -> Z {

        Z res = 0;

        if(left == 0 && right == 0) {
            if(a[i] < end) {
                if(lc || ac) {
                    res = 1;
                }
            } else if(a[i] == end) {
                res = 1;
            } else {
                if(ac || rc) {
                    res = 1;
                }
            }
        } else {

            // Z p_l = ((Z) left) / ((Z) left + right) * (1 - ((Z) choose(lc + ac + left + right - 1, lc + ac)) / ((Z) choose(lc + ac + left + right, lc + ac)));
            // Z p_r = ((Z) right) / ((Z) left + right) * (1 - ((Z) choose(rc + ac + left + right - 1, rc + ac)) / ((Z) choose(rc + ac + left + right, rc + ac)));

            // Z p_l = ((Z) left) / ((Z) left + right) * (lc + ac) / (lc + ac + left + right);
            // Z p_r = ((Z) right) / ((Z) left + right) * (rc + ac) / (rc + ac + left + right);

            Z p_l = z[left] * iz[left + right] * z[lc + ac] * iz[lc + ac + left + right];
            Z p_r = z[right] * iz[left + right] * z[rc + ac] * iz[rc + ac + left + right];

            res += p_l + p_r;
        }

        return res;
    };

    for(int i = 0; i < n; i++) {
        ld s = 0;
        // set<int> vis;
        int left = 0, right = 0, lc = 0, rc = 0, ac = 0, neutral = 0;

        Z total_res = 0;

        for(int j = 0; j < q; j++) {
            int end = ops[j][1] + (i - ops[j][0]);
            // m[end].push_back(ops[j]);
            if(ops[j][0] < i) {
                right++;
            } else if(ops[j][0] == i) {
                right++;
            } else {
                neutral++;
            }
        }

        if(a[i] < ttfang[0][0][1] + (i - ttfang[0][0][0])) total_res += get_p(i, a[i], left, right, lc ,rc, ac, neutral) * a[i];

        for(int j = 0; j < ttfang.size(); j++) {
            int end = ttfang[j][0][1] + (i - ttfang[j][0][0]);
            int nx = (j + 1 == ttfang.size() ? INT_MAX : ttfang[j + 1][0][1] + (i - ttfang[j + 1][0][0]));

            for(auto op : ttfang[j]) {
                if(op[0] < i) {
                    right--;
                    lc++;
                } else if(op[0] == i) {
                    right--;
                    ac++;
                } else {
                    neutral--;
                    rc++;
                }
            }

            total_res += get_p(i, end, left, right, lc ,rc, ac, neutral) * end;

            for(auto op : ttfang[j]) {
                if(op[0] < i) {
                    lc--;
                    neutral++;
                } else if(op[0] == i) {
                    ac--;
                    left++;
                } else {
                    rc--;
                    left++;
                }
            }

            if(end < a[i] && a[i] < nx) total_res += get_p(i, a[i], left, right, lc ,rc, ac, neutral) * a[i];
        }

        cout << total_res * fact[q] << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <algorithm>
// #include <bitset>
// #include <complex>
// #include <deque>
// #include <exception>
// #include <fstream>
// #include <functional>
// #include <iomanip>
// #include <ios>
// #include <iosfwd>
// #include <iostream>
// #include <istream>
// #include <iterator>
// #include <limits>
// #include <list>
// #include <locale>
// #include <map>
// #include <memory>
// #include <new>
// #include <numeric>
// #include <ostream>
// #include <queue>
// #include <set>
// #include <sstream>
// #include <stack>
// #include <stdexcept>
// #include <streambuf>
// #include <string>
// #include <typeinfo>
// #include <utility>
// #include <valarray>
// #include <vector>
// #include <array>
// #include <atomic>
// #include <chrono>
// #include <condition_variable>
// #include <forward_list>
// #include <future>
// #include <initializer_list>
// #include <mutex>
// #include <random>
// #include <ratio>
// #include <regex>
// #include <scoped_allocator>
// #include <system_error>
// #include <thread>
// #include <tuple>
// #include <typeindex>
// #include <type_traits>
// #include <unordered_map>
// #include <unordered_set>
// #include <cassert>
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
    
//     int n, m, q; cin >> n >> m >> q;

//     vector<int> a(n);
//     for(int &x : a) cin >> x;

//     vector<array<int,2>> ops(q);
//     for(auto &op : ops) {
//         cin >> op[0] >> op[1];
//         op[0]--;
//     }

//     vector<Z> res(n);

//     //case where slider i is never moved
//     for(int i = 0; i < n; i++) {
//         int f = 0;
//         for(int j = 0; j < q; j++) {
//             auto [idx, x] = ops[j];
//             if(idx < i) {
//                 if(x + (i - idx) > a[i]) f = 1;
//             } else if(i < idx) {
//                 if(x - (idx - i) < a[i]) f = 1;
//             } else {
//                 f = 1;
//             }
//         }
//         if(f == 0) {
//             res[i] = fact[q] * a[i];
//         }
//     }

//     for(int i = 0; i < q; i++) {
//         auto [last_op_idx, last_x] = ops[i];
//         //counting permutations where operation i is the last operation that moves slider j. 
//         for(int j = 0; j < n; j++) {
//             //case where j is >= last op idx so this operation pushes index j to the right or maxes it. 
//             if(j >= last_op_idx) {
                
                


//                 int f = 0;
//                 int noac = 0, ac = 0, pre = 0;
//                 for(int k = 0; k < q; k++) {
//                     //do not consider operation i again. 
//                     if(k == i) continue;


//                     // if()


//                 }
//             }
//         }
//     }

//     for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     init_fact();

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }