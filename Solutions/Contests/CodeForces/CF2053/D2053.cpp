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

vector<Z> fact(1,1);
vector<Z> inv_fact(1,1);

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    while(fact.size() < n + 1) {
        fact.push_back(fact.back() * fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<vector<ll>>> a(2, vector<vector<ll>>(n,vector<ll>(2)));
    vector<vector<int>> atidx(2,vector<int>(n));
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j][0];
            a[i][j][1] = j;
        }
        sort(a[i].begin(), a[i].end());
        for(int j = 0; j < n; j++) {
            atidx[i][a[i][j][1]] = j;
        }
    }
    Z res = 1;
    for(int i = 0; i < n; i++) {
        res *= min(a[0][i][0], a[1][i][0]);
    }
    // cout << "start a, b\n";
    // for(int j = 0; j < 2; j++) {
    //     for(int k = 0; k < n; k++) {
    //         cout << a[j][k][0] << " \n"[k == n - 1];
    //     }
    // }
    cout << res << " ";
    for(int i = 0; i < q; i++) {
        int o, x; cin >> o >> x;
        o--; x--;
        int s = atidx[o][x];
        int l = 0, r = n - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(a[o][s][0] >= a[o][m][0]) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        int e = l;
        res /= min(a[0][s][0], a[1][s][0]);
        if(s != e) {
            res /= min(a[0][e][0], a[1][e][0]);
        }        
        int si = a[o][s][1];
        int ei = a[o][e][1];
        swap(a[o][s], a[o][e]);
        swap(atidx[o][si], atidx[o][ei]);
        a[o][e][0]++;
        res *= min(a[0][s][0], a[1][s][0]);
        if(s != e) {
            res *= min(a[0][e][0], a[1][e][0]);
        }
        cout << res << " \n"[i == q - 1];
        // cout << "s : " << s << " e : " << e << '\n';
        // cout << "after a, b\n";
        // for(int j = 0; j < 2; j++) {
        //     for(int k = 0; k < n; k++) {
        //         cout << a[j][k][0] << " \n"[k == n - 1];
        //     }
        // }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}