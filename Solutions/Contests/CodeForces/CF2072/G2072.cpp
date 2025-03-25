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
const int MAXN = 1e6 + 1;
vector<Z> fact(MAXN), inv_fact(MAXN), res(MAXN), pows(MAXN);

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
    ll n, k; cin >> n >> k;

    auto rev = [](ll n, ll p) -> Z {
        Z res = 0;
        while(n) {
            res *= p;
            res += n % p;
            n /= p;
        }
        return res;
    };

    ll p = sqrt(n);
    while(p * p > n) p--;
    while(p * p <= n) p++;

    Z res = 0;

    for(int i = 2; i < p && i <= k; i++) {
        res += rev(n, i);
    }

    // cout << "up to before p res : " << res << '\n';

    // cout << "start p : " << p << '\n';

    while(p <= n && p <= k) {
        int X = n / p % p;
        int Y = n % p;
        Z a = min(1LL + Y / X, k - p + 1);
        Z x = X;
        Z y = Y;
        // Z add = a * (x + y * p) - y * a * (a - 1) / 2 - x * p * a * (a - 1) / 2 + x * (a - 1) * a * (2 * a - 1) / 6;
        Z add = a * (x + y * p) + a * (a - 1) / 2 * (-p * x + y) + (a - 1) * a * (2 * a - 1) / 6 * (-x);
        res += add;
        // cout << "p : " << p << " x : " << x << " y : " << y << " a : " << a << " add : " << add << '\n';
        p += a.x;
    }

    // cout << "p after : " << p << '\n';

    // cout << "p res : " << res << '\n';

    if(p <= k) {
        res += Z(k - p + 1) * n;
    }

    cout << res << '\n';

    // Z bfres = 0;
    // int l = 9, r = 17;
    // Z rangesum = 0;
    // for(int i = 2; i <= k; i++) {
    //     bfres += rev(n, i);
    //     if(i == n) {
    //         cout << "p bfres : " << bfres << '\n';
    //     }
    //     if(i >= l && i <= r) {
    //         rangesum += rev(n, i);
    //     }
    //     if(i == r) {
    //         cout << "range sum : " << rangesum << '\n';
    //     }
    // }
    // cout << "bfres : " << bfres << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}