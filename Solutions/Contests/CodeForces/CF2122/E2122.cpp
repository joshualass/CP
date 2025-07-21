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
    
    int n, k; cin >> n >> k;
    vector<vector<int>> a(2, vector<int>(n));
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
    }

    auto cnt_ways = [&](int delta, int lo, int hi) -> int {
        if(lo == -1 && hi == -1) {
            return max(0, k - abs(delta));
        } else if(lo == -1) {
            int test_lo = hi + delta;
            return 1 <= test_lo && test_lo <= k;
        } else if(hi == -1) {
            int test_hi = lo - delta;
            return 1 <= test_hi && test_hi <= k;
        } else {
            return lo - hi == delta;
        }
    };

    Z ways_free = 1 * (a[0][0] == -1 ? k : 1) * (a[1][n-1] == -1 ? k : 1);
    vector<Z> dp(k), nxdp(k);
    for(int i = 1; i < n; i++) {
        nxdp.assign(k, 0);
        Z nx_free = 0;
        int lo = a[1][i-1], hi = a[0][i];
        for(int delta = -k + 1; delta <= k - 1; delta++) {
            int ways_delta = cnt_ways(delta, lo, hi);
            if(delta > 0) {
                nxdp[delta] += ways_free * ways_delta;
            } else {
                nx_free += ways_free * ways_delta;
            }
            for(int j = 0; j < k; j++) {
                if(delta > 0) {
                    nxdp[delta] += dp[j] * ways_delta;
                } else {
                    if(j + delta >= 0) {
                        nxdp[j + delta] += dp[j] * ways_delta;
                    }
                }
            }
        }
        swap(dp, nxdp);
        swap(ways_free, nx_free);
    }

    cout << ways_free + accumulate(dp.begin(), dp.end(), Z(0)) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}