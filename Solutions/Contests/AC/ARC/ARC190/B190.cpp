#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//if you choose, you lose. 

/*
This problem has what I think to be a very tight time limit.
This problem requires us to do the ELuo efficient inverse factorial choose method
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
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
const int MAXN = 1e7;
vector<Z> fact(MAXN), inv_fact(MAXN), res(MAXN), pows(MAXN);

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(int n) {
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact(1e7);

    int n, a, b; cin >> n >> a >> b;
    a--; b--;

    pows[0] = Z(1);
    for(int i = 1; i <= n; i++) {
        pows[i] = pows[i-1] * 4;
    }

    auto solve0 = [&](int n, int a, int b) { //a, b, 0-indexed
        Z c = 1;
        for(int k = n; k >= 2; k--) {
            res[k] += c * choose(n - k, b) * pows[k-2];
            c *= 2;
            c -= choose(n - k, a - k + 1);
            c -= choose(n - k, a);
        }
    };

    auto solve1 = [&](int n, int a, int b) {
        solve0(n, a, b);
        solve0(n, b, a);
        for(int k = n; k >= 2; k--) {
            res[k] -= choose(n - k, a) * choose(n - k, b) * pows[k-2];
        }
    };

    for(int i = 0; i < 4; i++) {
        solve1(n, a, b);
        int na = b, nb = n - a - 1;
        a = na, b = nb;
    }

    res[1] = choose(n - 1, a) * choose(n - 1, b);

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        cout << res[x] << '\n';
    }

    return 0;
}