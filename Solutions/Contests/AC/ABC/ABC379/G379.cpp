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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w; cin >> h >> w;
    vector<string> a(h);
    for(auto &x : a) cin >>x;

    if(w > h) {
        vector<string> b(w, string(h, '.'));
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                b[j][i] = a[i][j];
            }
        }
        swap(h,w);
        a = b;
    }

    auto decrypt = [&](int bm, int pos) -> vector<int> {
        vector<int> res;
        for(int i = 0; i < w; i++) {
            if(i == 0 || i == pos) {
                res.push_back(bm % 3);
                bm /= 3;
            } else {
                res.push_back((res.back() + 1 + (bm & 1)) % 3);
                bm /= 2;
            }
        }
        return res;
    };

    auto encrypt = [&](vector<int> b, int pos) -> int {
        vector<int> m;
        for(int i = 0; i < w; i++) {
            if(i == 0 || i == pos) {
                m.push_back(b[i]);
            } else {
                if((b[i-1] + 1) % 3 == b[i]) {
                    m.push_back(0);
                } else {
                    m.push_back(1);
                }
            }
        }
        int res = 0;
        for(int i = w - 1; i >= 0; i--) {
            if(i == 0 || i == pos) {
                res *= 3;
            } else {
                res *= 2;
            }
            res += m[i];
        }
        return res;
    };

    int len = 9 * max(1, 1 << (w - 2));

    vector<Z> dp(len), next(len);

    //create first row dp
    for(int i = 0; i < 3 * (1 << (w - 1)); i++) {
        vector<int> b = decrypt(i, 0);
        int ok = 1;
        for(int j = 0; j < w; j++) {
            if(a[0][j] != '?' && a[0][j] - '1' != b[j]) ok = 0;
        }
        dp[i] = ok;
    }

    for(int i = 1; i < h; i++) {
        for(int j = 0; j < w; j++) {
            for(int k = 0; k < len; k++) {
                next[k] = 0;
            }
            for(int k = 0; k < len; k++) {
                vector<int> b = decrypt(k, j);
                Z c = dp[k];
                for(int l = 0; l < 3; l++) {
                    int ok = 1;
                    if(l == b[j] || j && l == b[j - 1]) ok = 0;
                    if(a[i][j] != '?' && a[i][j] - '1' != l) ok = 0;
                    if(ok) {
                        swap(l, b[j]);
                        next[encrypt(b, j + 1)] += c;
                        swap(l, b[j]);
                    }
                }
            }
            swap(dp, next);
        }
    }
    Z res = 0;
    for(int i = 0; i < len; i++) {
        res += dp[i];
    }

    cout << res << '\n';

    //diagonals are no good. 

    // int n; cin >> n;

    // vector<int> a(n + 1);
    // a[0] = 1;
    // for(int i = 1; i <= n; i++) {
    //     a[i] = a[i-1] * 3;
    // }

    // auto get_color = [&](int hash) -> vector<int> {
    //     vector<int> res;
    //     for(int i = 0; i < n; i++) {
    //         res.push_back(hash % 3);
    //         hash /= 3;
    //     }
    //     return res;
    // };

    // int res = 0;
    // for(int i = 0; i < a[n]; i++) {
    //     vector<int> b = get_color(i);
    //     int c = 1;
    //     for(int j = 1; j < n; j++) {
    //         if(b[j-1] == b[j]) c *= 2;
    //     }
    //     res += c;
    // }

    // cout << res << '\n';

    return 0;
}