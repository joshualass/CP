#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}


void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for(int &x : a) cin >> x;

// int solve(vector<int> a) {
//     int n = a.size() - 1;

    int ok = 1;
    int cnt = 0;
    
    //first, pair up everything that can be paired up. 
    for(int i = 1; i <= n; i++) {
        if(a[i] != -1) {
            int to = a[i];
            if(to) {
                if(to > n) {
                    ok = 0;
                    break;
                }
                if(a[to] == -1) {
                    a[to] = i;
                } else if(a[to] != i ) {
                    ok = 0;
                }
            }
        }
    }

    //after everything is paired up, count the unknowns
    for(int i = 1; i <= n; i++) {
        if(a[i] == -1) cnt++;
    }

    // cout << "n : " << n << '\n';
    // cout << "a : " << a << '\n';
    // cout << "ok : " << ok << "\n";
    // cout << "cnt : " << cnt << '\n';

    vector<Z> dp(cnt + 1);
    dp[0] = 1;

    for(int i = 1; i <= cnt; i++) {
        if(i == 1) {
            dp[i] = 2;
        } else {
            dp[i] = dp[i-1] * 2 + (i - 1) * dp[i - 2];
        }
        if(i == cnt && a[n] == -1) dp[i] -= dp[i - 1];
    }

    // cout << "dp : " << dp << '\n';

    cout << dp[cnt] * ok << '\n';

    // return (dp[cnt] * ok).x;

}

int solve_calls = 0;

int solve_slow(vector<int> a) {
    solve_calls++;
    cout << solve_calls << " <- count a -> " << a << '\n';
    if(solve_calls == 105) {
        assert(0);
    }
    int cnt = 0;
    auto c = [&](vector<int> b) {
        // cout << "cand b : " << b << '\n';
        vector<int> res(b.size());
        for(int i = 1; i < b.size(); i++) {
            if(b[i] < 0 || b[i] >= b.size()) return;
            res[b[i]] += i;
        }
        if(b == res && b.back()) {
            cnt++;
            // cout << "good b : " << b << '\n';
        }
    };

    auto dfs = [&](auto self, int idx) -> void {
        if(idx == a.size()) {
            c(a);
            return;
        }
        if(a[idx] == -1) {
            int stop = (idx ? a.size() : a.size() * a.size());
            for(int i = 0; i <= stop; i++) {
                a[idx] = i;
                self(self, idx + 1);
            }
            a[idx] = -1;
        } else {
            self(self, idx + 1);
        }
    };

    dfs(dfs, 0);
    return cnt;
}   

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // solve_slow({-1, -1, -1, 1, 0, -1});
    // solve_slow({-1, 0, 3, -1});

    // cout << solve_slow({-1, -1, 5, 0, -1}) << '\n';
    // cout << "solve : " << solve({-1, -1, 5, 0, -1}) << '\n';

    // int n = 2;
    // while(n < 6) {
    //     vector<int> a(n + 1, -1);
    //     auto dfs = [&](auto self, int idx) -> void {
    //         if(idx == n) {
    //             int slow_res = solve_slow(a);
    //             int fast_res = solve(a);
    //             if(slow_res != fast_res) {
    //                 cout << "WA slow : " << slow_res << " fast : " << fast_res << '\n';
    //                 cout << "a : " << a << '\n';
    //                 assert(0);
    //             }
    //             return;
    //         }
    //         for(int i = -1; i <= n + 2; i++) {
    //             a[idx] = i;
    //             self(self, idx + 1);
    //         }
    //         a[idx] = -1;
    //     };
    
    //     dfs(dfs, 1);
    //     n++;
    // }


    // cout << "all ok!\n";

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}