#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

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

const int H = 5;

template<class T, size_t L>
array<T, L> operator*(array<T, L> &lhs, array<T, L> &rhs) {
    array<T, L> res = {};
    for(int i = 0; i < L; i++) res[i] = lhs[i] * rhs[i];
    return res;
}

template<class T, size_t L>
void operator*=(array<T, L> &lhs, array<T, L> &rhs) {
    for(int i = 0; i < L; i++) lhs[i] *= rhs[i];
}

void solve() {
    
    int l, w, h; cin >> l >> w >> h;
    int k, r; cin >> k >> r;

    vector<array<Z,H>> a(k), ra(k);
    array<Z,H> ident = {};
    for(int i = 0; i < H; i++) ident[i] = 1;

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < H; j++) {
            a[i][j] = rng();
            ra[i][j] = 1 / a[i][j];
        }
    }

    int s;
    if(l <= w && l <= h) {
        s = 0;
        swap(l, l);
    } else if(w <= l && w <= h) {
        s = 1;
        swap(l, w);
    } else if(h <= l && h <= w) {
        s = 2;
        swap(l, h);
    }

    // cout << "s : " << s << endl;

    vector<vector<array<int,5>>> upds(h + 1); //{x1, y1, x2, y2, id}

    vector<int> cnts(k);

    for(int q = 0; q < r; q++) {
        int i, x1, y1, z1, x2, y2, z2; cin >> i >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        if(s == 1) {
            swap(x1, y1);
            swap(x2, y2);
        } else if(s == 2) {
            swap(x1, z1);
            swap(x2, z2);
        }
        i++;
        upds[z1].push_back({x1, y1, x2, y2, i});
        upds[z2 + 1].push_back({x1, y1, x2, y2, -i});
        // cout << "k : " << k << " i : " << i << endl;
        cnts[i - 1]++;
    }

    set<array<int,H>> good;

    auto conv = [&](array<Z,H> a) -> array<int,H> {
        array<int,H> res = {};
        for(int z = 0; z < H; z++) res[z] = a[z].x;
        return res;
    };

    for(int i = 0; i < k; i++) {
        auto cur = ident;
        for(int j = 1; j <= cnts[i]; j++) {
            cur = cur * a[i];
            array<int,H> intmode = {};
            for(int z = 0; z < H; z++) intmode[z] = cur[z].x;
            good.insert(intmode);
        }
    }

    vector<vector<array<Z,H>>> b(l, vector<array<Z,H>>(w, ident));
    int res = 0;

    // cout << "l : " << l << " w : " << w << " h : " << h << endl;

    for(int s = 0; s < h; s++) {
        vector<vector<array<Z,H>>> p(l, vector<array<Z,H>>(w + 1, ident));
        for(auto [x1, y1, x2, y2, i] : upds[s]) {
            auto cur = a[abs(i) - 1];
            auto rev = ra[abs(i) - 1];
            if(i < 0) swap(cur, rev); 
            // cout << "x1 : " << x1 << " x2 " << x2 << " y1 : " << y1 << " y2 : " << y2 << endl;
            for(int j = x1; j <= x2; j++) {
                p[j][y1] *= cur;
                p[j][y2 + 1] *= rev;
            }
        }
        for(int i = 0; i < l; i++) {
            for(int j = 0; j < w; j++) {
                if(j) {
                    p[i][j] *= p[i][j-1];

                }
                b[i][j] *= p[i][j];
                res += good.count(conv(b[i][j]));
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}