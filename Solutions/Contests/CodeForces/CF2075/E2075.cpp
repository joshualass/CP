#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*



*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto x : v) os << (x < 10 ? " " : "") << x << " ";
    // os << v.size() << ' ';
    // for(int i = 0; i < v.size(); i++) if(i == 0 || v[i] != v[i-1]) os << i << ", s : " << v[i] << " ";
    for(int i = 0; i < v.size(); i++) if(__builtin_popcount(i) <= 1) os << "i : " << i << ", s : " << v[i] << " ";
    // os << v.size() 
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

int get_cnt(int x, int y) {

    if(y > x) return 0;

    int b = 31 - __builtin_clz(y);
    int left = x - y;
    int res = 0;
    int free = x >> (b + 1);
    res += free << b;

    if(x & y) {
        res += 1 + (((1 << b) - 1) & left);
    }
    return res;
}

void solve() {
    
    int n, m, a, b; cin >> n >> m >> a >> b;

    Z res = 1LL * (a + 1) * (b + 1); //1, 1
    //a - 1, b - 2
    res += Z(a + 1) * Z(1LL * b * (b + 1) / 2) * Z(power<Z>(2, m) - 2);
    //a - 2, b - 1
    res += Z(1LL * a * (a + 1) / 2) * Z(b + 1) * Z(power<Z>(2, n) - 2);
    //a - 2, b - 2
    // res += Z(min(a,b) * (min(a,b) + 1) / 2) * (power<Z>(2, n) - 2) * (power<Z>(2, m) - 2);

    Z combo = 0;

    for(int i = 0; i < 29; i++) {
        Z a_ways = get_cnt(a, 1 << i);
        Z b_ways = get_cnt(b, 1 << i);
        Z add = a_ways * b_ways * (power<Z>(2, n) - 2) * (power<Z>(2, m) - 2) * (1 << i);
        // cout << "i : " << i << " add : " << add << '\n';
        combo += add;
    }

    // cout << "combo : " << combo << '\n';

    res += combo;

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int res = 0;
    // vector<vector<int>> a(2, vector<int>(2));
    // for(int i = 0; i < 3; i++) {
    //     for(int j = 0; j < 3; j++) {
    //         for(int k = 0; k < 3; k++) {
    //             for(int l = 0; l < 3; l++) {
    //                 set<int> s = {i ^ k, i ^ l, j ^ k, j ^ l};
    //                 if(s.size() <= 2) {
    //                     res++;
    //                     set<int> b = {i,j}, c = {k,l};
    //                     a[b.size() - 1][c.size() - 1]++;    
    //                 }
    //             }
    //         }
    //     }
    // }

    // cout << res << '\n';

    // for(int i = 0; i < 2; i++) {
    //     for(int j = 0; j < 2; j++) {
    //         cout << a[i][j] << " \n"[j == 1];
    //     }
    // }

    // for(int A = 1; A <= 16; A++) {
    //     vector<int> a(1 << (32 - __builtin_  clz(A)));
    //     for(int i = 0; i <= A; i++) {
    //         vector<int> t(1 << (32 - __builtin_clz(A)));
    //         for(int j = 0; j <= A; j++) {
    //             // t[i^j]++;
    //             a[i^j]++;
    //         }
    //         // cout << "A : " << bitset<8>(A) << " poss : " << 
    //     }
    //     // cout << "A + 1 : " << bitset<8>(A + 1) << " vec : " << a << '\n';
    //     // cout << "A : " << A << " vec : " << a << '\n';
    //     // cout << "ans : " << a[256] << '\n';
    //     cout << "A : " << A << '\n';
    //     for(int i = 1; i <= A; i++) {
    //         if(__builtin_popcount(i) == 1) {
    //             cout << "i : " << i << " a[i] : " << a[i] << " get_cnt(A, i) : " << get_cnt(A, i) << '\n';
    //         }
    //     }
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}