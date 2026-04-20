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

const int maxn = 1e3;
Z dp[maxn + 1][3][maxn + 1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    set<int> s;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        s.insert(x);
    }

    int need = sz(s);
    Z res = n;
    int unused = m - need;

    dp[0][0][0] = 1;

    for(int i = 0; i <= need; i++) {
        for(int j = 0; j <= 2; j++) {
            for(int k = 0; k <= unused; k++) {
                int unvis = m + 1 - i - (j == 2) - k;
                // cout << "i : " << i << " j : " << j << " k : " << k << " uv : " << unvis << " dp : " << dp[i][j][k] << endl;
                Z add = 0;
                if(j == 0 && i < need) {
                    //case visit backspace
                    {
                        Z p = Z(1) / unvis;
                        if(i == 0) {
                            add += dp[i][j][k] * p;
                            dp[i][2][k] += dp[i][0][k] * p;
                        } else {
                            add += dp[i][j][k] * p * 2;
                            dp[i][2][k] += dp[i][0][k] * p;
                        }
                    }
                    //case visit next correct
                    {
                        Z p = Z(1) / unvis;
                        dp[i+1][0][k] += dp[i][0][k] * p;
                    }
                    //case visit wrong later use
                    {
                        Z p = Z(need - i - 1) / unvis;
                        add += dp[i][j][k] * p * 2;
                        dp[i+1][1][k] += dp[i][0][k] * p;
                    }
                    //case visit wrong no use
                    if(k < unused) {
                        {
                            Z p = Z(unused - k) / unvis;
                            add += dp[i][j][k] * p * 2;
                            dp[i][1][k+1] += dp[i][j][k] * p;
                        }
                    }
                }

                if(j == 1) {
                    //case visit backspace
                    {
                        Z p = Z(1) / unvis;
                        //we have already added this cost so dont add to cost
                        dp[i][2][k] += dp[i][j][k] * p;
                    }
                    //case visit next correct / wrong later use are now same case
                    {
                        if(i < need) {
                            Z p = Z(need - i) / unvis;
                            add += dp[i][j][k] * p * 2;
                            dp[i+1][1][k] += dp[i][j][k] * p;
                        }
                    }
                    //case visit wrong no use
                    if(k < unused) {
                        {
                            Z p = Z(unused - k) / unvis;
                            add += dp[i][j][k] * p * 2;
                            dp[i][1][k+1] += dp[i][j][k] * p;
                        }
                    }
                }

                if(j == 2 && i < need) {
                    //case visit next correct
                    {
                        Z p = Z(1) / unvis;
                        dp[i+1][2][k] += dp[i][j][k] * p;
                    }
                    //case visit wrong later use
                    {
                        Z p = Z(need - i - 1) / unvis;
                        add += dp[i][j][k] * p * 2;
                        dp[i+1][2][k] += dp[i][j][k] * p;
                    }
                    //case visit wrong no use
                    if(k < unused) {
                        {
                            Z p = Z(unused - k) / unvis;
                            add += dp[i][j][k] * p * 2;
                            dp[i][2][k+1] += dp[i][j][k] * p;
                        }
                    }
                }

                // cout << "add : " << add << endl;
                res += add;
            }
        }
    }

    cout << res << '\n';

    // cout << Z(118) / 24 << endl;

    return 0;
}
