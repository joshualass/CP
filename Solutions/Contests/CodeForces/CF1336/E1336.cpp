#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int d = 35;
struct B {

    array<ll,d> basis = {};
    B(): basis({}) {}

    B& operator=(const B& other) {
        this->basis = other.basis;
        return *this;
    }

    B operator+(const B& other) const {
        B res;
        res.basis = this->basis;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(other.basis[bit]) res.insert(other.basis[bit]);
        }
        return res;
    }

    bool insert(ll x) { //return 0/1 if the insert failed. 
        // cout << "insert x : " << x << '\n';
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    basis[bit] = x;
                    return 1;
                }
            }
        }
        return 0;
    }

    bool find(ll x) { //return 0/1 if element is in the basis, does not insert. 
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    return 0;
                }
            }
        }
        return 1;
    }

    ll query() {
        ll res = 0;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((res >> bit) & 1) == 0) res ^= basis[bit];
        }
        return res;
    }
};

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

const int mm = 35;
const int mr = 11;

ll pc[1 << (mm - mr)];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    B b;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        b.insert(x);
    }

    vector<ll> a;
    for(ll x : b.basis) if(x) a.push_back(x);

    int l = min((int) a.size(), mm - mr); //size of basis of lhs
    int r = a.size() - l; //size of basis of rhs

    vector<ll> rhs(a.begin(), a.begin() + r), lhs(a.begin() + r, a.end()); //bases

    // cout << "lhs : " << lhs << '\n';

    for(int i = 0; i < l; i++) pc[1LL << i] = lhs[i];

    vector<vector<Z>> lc(1 << mr, vector<Z>(mm - mr + 1)); //constant size of 11. 
    for(int i = 0; i < 1 << l; i++) {
        if(i) {
            int bm = (i - 1) & i;
            pc[i] = pc[bm] ^ pc[i ^ bm];
        }
        lc[pc[i] & ((1 << mr) - 1)][__builtin_popcountll(pc[i] >> mr)] += 1;
    }

    // for(int i = 0; i < 1 << mr; i++) {
    //     cout << "i : " << i << " lc[i] : " << lc[i] << '\n';
    // }

    vector<Z> res(mm + 1);
    vector<ll> pcr(1 << r);

    for(int i = 0; i < r; i++) pcr[1LL << i] = rhs[i];

    for(int i = 0; i < 1 << r; i++) {

        if(i) {
            int bm = (i - 1) & i;
            pcr[i] = pcr[bm] ^ pcr[i ^ bm];
        }
        // cout << "i : " << i << " pcr i : " << pcr[i] << '\n';
        for(int j = 0; j < 1 << mr; j++) {
            for(int k = 0; k < mm - mr + 1; k++) {
                res[__builtin_popcount(pcr[i] ^ j) + k] += lc[j][k];
            }
        }
    }

    for(int i = 0; i <= m; i++) cout << res[i] * power<Z>(2, n - a.size()) << " \n"[i == m];

    return 0;
}
