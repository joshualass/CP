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


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, L; cin >> n >> L;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    //given that we are at state with longest matching prefix index i, length match prefix of j and appending character k. stores the {next longest prefix, length, bitmask contribution}
    vector pc(n, vector(11, vector<array<int,3>>(26, {-1,-1,-1})));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= a[i].size(); j++) {
            for(int k = 0; k < 26; k++) {
                string s = a[i].substr(0, j);
                s.push_back(k + 'a');
                int to = 0, len = 0;
                for(int l = 0; l < n; l++) {
                    for(int m = 1; m <= min(s.size(), a[l].size()); m++) {
                        if(s.substr(s.size() - m) == a[l].substr(0, m) && m > len) {
                            to = l;
                            len = m;
                        }
                    }
                }
                int bm = 0;
                for(int l = 0; l < n; l++) {
                    if(s.find(a[l]) != string::npos) {
                        bm += 1 << l;
                    }
                }
                pc[i][j][k] = {to, len, bm};
            }
        }
    }

    vector dp(L + 1, vector(n, vector(11, vector<Z>(1 << n))));
    dp[0][0][0][0] = 1;

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < 11; k++) {
                for(int bm = 0; bm < 1 << n; bm++) {
                    if(dp[i][j][k][bm].x) {
                        for(int l = 0; l < 26; l++) {
                            auto [nxj, nxk, bmcontrib] = pc[j][k][l];
                            dp[i + 1][nxj][nxk][bm | bmcontrib] += dp[i][j][k][bm];
                        }
                    }
                }
            }
        }
    }

    Z res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 11; j++) {
            res += dp[L][i][j][(1 << n) - 1];
        }
    }

    cout << res << '\n';

    return 0;
}
