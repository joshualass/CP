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

Z dp[500][3][1 << 10][2];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n; cin >> n;
    reverse(n.begin(), n.end());

    for(int i = sz(n) - 1; i >= 0; i--) {
        int here = n[i] - '0';
        // cout << "i : " << i << " here : " << here << endl;
        //try spawning in the next number
        for(int nx = 1; nx <= 9; nx++) {
            if(i == sz(n) - 1 && nx > here) continue;
            int nxj = nx % 3;
            int nxk = 1 << nx;
            int nxl = i == sz(n) - 1 && nx == here;
            dp[i][nxj][nxk][nxl] += 1;
            // cout << "add i : " << i << " j : " << nxj << " k : " << nxk << " l : " << nxl << endl;
        }
        if(i == 0) continue;
        int nxhere = n[i-1] - '0';
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 1 << 10; k++) {
                for(int l = 0; l < 2; l++) {
                    for(int nx = 0; nx < 10; nx++) {
                        int nxi = i - 1;
                        int nxj = (j + nx) % 3;
                        int nxk = k | (1 << nx);
                        int nxl = l && nx == nxhere;
                        if(l && nx > nxhere) continue;
                        // if(dp[i][j][k][l].x) {
                        //     cout << "transition i : " << i << " j : " << j << " k : " << k << " l : " << l << " to nx : " << nx << " nxi : " << nxi << " nxj : " << nxj << " nxk : " << nxk << " nxl : " << nxl << endl;
                        // }
                        dp[nxi][nxj][nxk][nxl] += dp[i][j][k][l];
                    }
                }
            }
        }
    }

    Z res = 0;
    for(int i = 0; i < 3; i++) {
        for(int k = 0; k < 1 << 10; k++) {
            int cnt = 0;
            if(__builtin_popcount(k) == 3) cnt++;
            if(i == 0) cnt++;
            if((k >> 3) & 1) cnt++;
            // cout << "i : " << i << " k : " << k << " cnt : " << cnt << endl;
            if(cnt == 1) {
                for(int l = 0; l < 2; l++) {
                    res += dp[0][i][k][l];
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}
