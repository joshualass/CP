#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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
    
    int n; cin >> n;
    int x, y; cin >> x >> y;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    if(x > y) {
        x = n - x;
        y = n - y;
        reverse(a.begin(), a.end());
    } else {
        x--; 
        y--;
    }

    Z half = Z(1) / 2;
    vector<ll> p(n + 1);
    for(int i = 1; i <= n; i++) {
        p[i] = p[i-1] + (i - 1 == x || i - 1 == y ? a[i-1] : b[i-1]);
    }

    auto get_p = [&](int l, int r, int nx) -> Z {
        ll s = p[r] - p[l];
        int tot = 0;
        if(l && s >= a[l-1]) tot++;
        if(r < n && s >= a[r]) tot++;
        int pos = s >= a[nx];
        if(!pos) return 0;
        if(tot == 1) return 1;
        return half;
    };

    auto work = [&](int start) -> vector<vector<Z>> {
        vector<vector<Z>> dp(n + 1, vector<Z>(n)); //dp[t][i] -> probability that at time t, fish i is eaten by 
        dp[1][start] = 1;
        for(int time = 2; time <= n; time++) {
            for(int i = 0; i < n; i++) {
                if(x > i) { 
                    if(i + 1 < n) {
                        dp[time][i] += dp[time - 1][i + 1] * get_p(i + 1, i + 1 + (time - 1), i);
                    }
                    if(i + time - 1 < n) {
                        dp[time][i] += dp[time - 1][i + time - 1] * get_p(i + 1, i + 1 + (time - 1), i);
                    }
                }
                if(x < i) {
                    if(i) {
                        dp[time][i] += dp[time - 1][i - 1] * get_p(i - (time - 1), i, i);
                    }
                    if(i - time + 1 >= 0) {
                        dp[time][i] += dp[time - 1][i - time + 1] * get_p(i - (time - 1), i, i);
                    }
                }
            }
        }
        return dp;
    };

    auto dpa = work(x), dpb = work(y);
    vector<vector<Z>> dpm(n + 1, vector<Z>(n));

    for(int )

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}