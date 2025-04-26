#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<Z> p(n);
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        p[i] = a;
        p[i] /= b;
    }
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Z res = 0;
    Z evl = 0;

    vector<Z> ps(n); //product of the probability of all of node i's neighbors. 
    vector<Z> pinds(n); //sum of (1 - p_i) / p_i for all neighbors of i. 
    vector<Z> pl(n); //probability that node i is a leaf, very independent

    auto dfs = [&](auto self, int i, int par) -> void {

        Z prod = 1;
        Z ind_sum = 0;

        for(int c : adj[i]) {
            prod *= p[c];
            ind_sum += (1 - p[c]) / p[c];
        }
        Z ind_p = (1 - p[i]) * prod * ind_sum;

        res += evl * ind_p;
        evl += ind_p;

        ps[i] = prod;
        pl[i] = ind_p;
        pinds[i] = ind_sum;

        Z evlin = 0, evlout = 0, evind = 0;

        for(int c : adj[i]) {
            if(c != par) {
                self(self, c, i);

                //direct connections
                res -= pl[i] * pl[c];
                //uncount
                Z add_pair = (1 - p[i]) * (1 - p[c]) * ps[i] * ps[c] / p[i] / p[c];
                // cout << "i : " << i << " c : " << c << " ap : " << add_pair << '\n';
                res += add_pair;

            }

            //node i is the center of the connections
            //uncount
            res -= evind * pl[c];
            evind += pl[c];
            //in
            Z in = ps[c] / p[i] * (1 - p[c]);
            // cout << "i : " << i << " c : " << c << " in : " << in << '\n';
            res += evlin * in * (1 - p[i]);
            evlin += in;
            //out  
            Z out = (1 - p[c]) * ps[c] / p[i] * (pinds[c] - (1 - p[i]) / p[i]);
            // cout << "i : " << i << " c : " << c << " out : " << out << '\n';
            res += evlout * out * p[i];
            evlout += out;
        }
    };

    dfs(dfs, 0, -1);

    // cout << "ps : " << ps << '\n';
    // cout << "pinds : " << pinds << '\n';
    // cout << "pl : " << pl << '\n';

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}