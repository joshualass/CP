#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

//orz Wobert nice int128 code
using i128 = __int128;
istream& operator>>(istream &is, i128 &x) {
    ll y; is >> y;
    x = y;
    return is;
}
// modified from https://codeforces.com/blog/entry/75044?#comment-1106835
ostream &operator<<(ostream &os, i128 x) {
    if (x == 0) return os << '0';
    if (x < 0) os << '-', x = -x;
    string s;
    while (x) s += char(x%10) + '0', x /= 10;
    reverse(s.begin(), s.end());
    return os << s;
}

i128 gcd(i128 x, i128 y) {
    if(y == 0) return x;
    return gcd(y, x % y);
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
    
    i128 n, m; cin >> n >> m;    

    i128 x = n;
    string s;
    while (x) s += char(x%10) + '0', x /= 10;
    reverse(s.begin(), s.end());

    vector<i128> p10(1, 1);
    while(sz(p10) <= sz(s)) p10.push_back(p10.back() * 10);

    Z res = 0;

    for(int i = 1; i <= sz(s); i++) {
        //x cnt
        i128 mult = p10[i];
        mult--;
        mult %= m;
        
        Z xcnt;
        if(mult == 0) {
            xcnt = n;
        } else {
            i128 f = m / gcd(mult, m);
            xcnt = n / f;
        }

        //y cnt
        Z ycnt = Z(min(p10[i] - 1, n)) - Z(p10[i - 1] - 1);
        if(i == 19) ycnt = 1;

        // cout << "i : " << i << " x : " << xcnt << " y : " << ycnt << '\n';

        res += xcnt * ycnt;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}