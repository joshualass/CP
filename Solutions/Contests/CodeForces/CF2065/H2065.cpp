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

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

struct Info {
    array<array<Z,3>,2> o;
    array<array<Z,2>,2> c;
    Info() {}
    Info(array<array<Z,3>,2> o, array<array<Z,2>,2> c): o(o), c(c) {}
};

Info operator+(const Info &lhs, const Info &rhs) {
    
    Info res;

    auto combo = [](array<array<Z,3>, 2> lhs, array<array<Z,3>, 2> rhs) -> array<array<Z,3>, 2> {
        return {
            array<Z,3>{lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1], lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1], lhs[0][2] * rhs[0][0] + lhs[1][2] * rhs[0][1] + rhs[0][2]},
            array<Z,3>{lhs[1][0] * rhs[0][1] + lhs[0][0] * rhs[1][0], lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1], lhs[0][2] * rhs[1][0] + lhs[1][2] * rhs[1][1] + rhs[1][2]}
        };
    };

    res.o = combo(lhs.o, rhs.o);

    return res;
}

void solve() {
    
    string s; cin >> s;
    int n = s.size();
    int b = (n + b - 1) / b;

    vector<Z> p2(n + 1);
    p2[0] = 1;
    for(int i = 1; i <= n; i++) p2[i] = p2[i-1] * 2;

    vector<array<array<Z,3>,2>> o(b);
    vector<array<array<Z,2>,2>> c(b);



    auto update_block = [&](int b_idx) -> void {
        array<array<Z, 3>, 2> cur = {array<Z,3>{1, 0, 0}, array<Z,3>{0, 1, 0}};
        array<array<Z, 2>, 2> output = {array<Z,2>{0, 0}, array<Z,2>{0, 0}};
        for(int i = b_idx * SQN; i < (b_idx + 1) * SQN && i < n; i++) {
            int after_cnt = n - i - 1;

            if(s[i] == '0') {
                output[0][0] += cur[1][0] * p2[after_cnt];
                output[1][0] += cur[1][1] * p2[after_cnt];
                output[0][1] += cur[1][2] * p2[after_cnt];
            } else {
                output[0][0] += cur[0][0] * p2[after_cnt];
                output[1][0] += cur[0][1] * p2[after_cnt];
                output[1][1] += cur[0][2] * p2[after_cnt];
            }

            array<array<Z,3>, 2> rhs = {};
            if(s[i] == '0') {
                rhs = {
                    array<Z,3>{2, 1, 1},
                    array<Z,3>{0, 1, 0}
                };
            } else {
                rhs = {
                    array<Z,3>{1, 0, 0},
                    array<Z,3>{1, 2, 1}
                };
            }
            cur = comb(cur, rhs);
        }

    };

    int q; cin >> q;




}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}