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

/*
init_fact()
*/

//RECENTLY MODIFIED AND COULD BE UNSTABLE. REMOVE ME WHEN THIS IS WORKING. 

const int MAXN = 500000;
int p = 0;
int trie[MAXN + 1][2];
int par[MAXN + 1], vis[MAXN + 1];
Z comp[MAXN + 1], incomp[MAXN + 1];

void update(int idx) {

    Z incompl, _compl, incompr, compr;

    if(trie[idx][0]) {
        incompl = incomp[trie[idx][0]];
        _compl = comp[trie[idx][0]];
    } else {
        incompl = 1;
        _compl = 0;
    }

    if(trie[idx][1]) {
        incompr = incomp[trie[idx][1]];
        compr = comp[trie[idx][1]];
    } else {
        incompr = 1;
        compr = 0;
    }

    Z res_comp = _compl * compr;
    if(vis[idx]) res_comp += (incompl + _compl) * (compr + incompr);

    Z res_incomp = incompl * (incompr + compr) + _compl * incompr;

    comp[idx] = res_comp;
    incomp[idx] = res_incomp;

    // cout << "idx : " << idx << " incompl : " << incompl << " _compl : " << _compl << " incompr : " << incompr << " compr : " << compr << '\n';
    // cout << "res_comp : " << res_comp << " res_incomp : " << res_incomp << '\n';

}

void insert(string s) {
    int cur = 0;
    for(char c : s) {
        int nx = c == 'B';
        if(trie[cur][nx] == 0) {
            trie[cur][nx] = ++p;
            par[trie[cur][nx]] = cur;
        }
        cur = trie[cur][nx];
        // cout << "cur : " << cur << '\n';
    }
    vis[cur] = 1;
    while(1) {
        update(cur);
        if(cur == 0) break;
        cur = par[cur];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        insert(s);
        cout << comp[0] << '\n';
    }

    return 0;
}