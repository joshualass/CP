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

vector<Z> fact(1,1);
vector<Z> inv_fact(1,1);

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    while(fact.size() < n + 1) {
        fact.push_back(fact.back() * fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    int ok = 1;

    vector conds(n + 1,vector<array<int,2>>(0));
    for(int i = 0; i < m; i++) {
        int l, r, x; cin >> l >> r >> x;
        conds[r].push_back({l,x});
        if(x > r - l + 1) ok = 0;
    }
    
    vector dp(n + 1, vector<Z>(n + 1));
    dp[0][0] = 1;

    for(int i = 2; i <= n; i++) {
        vector next(n + 1, vector<Z>(n + 1));
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                //add element of same color
                next[j][k] += dp[j][k];
                //add element of second color
                next[i - 1][k] += dp[j][k];
                //add element of third color
                if(j) {
                    next[i - 1][j] += dp[j][k];
                }
            }
        }
        for(auto [l, x] : conds[i]) {
            for(int j = 0; j <= n; j++) {
                for(int k = 0; k <= n; k++) {
                    if(x == 1) {
                        if(j >= l) {
                            next[j][k] = 0;
                        }
                    } else if(x == 2) {
                        if(k >= l || j < l) {
                            next[j][k] = 0;
                        }
                    } else if(x == 3) {
                        if(k < l) {
                            next[j][k] = 0;
                        }
                    }
                }
            }
        }
        swap(dp, next);
    }

    Z res = 0;
    for(int j = 0; j <= n; j++) {
        for(int k = 0; k <= n; k++) {
            if(j == 0) {
                res += dp[j][k] * 3;
            } else {
                res += dp[j][k] * 6;
            }
        }
    }

    cout << res * ok << '\n';

    return 0;
}