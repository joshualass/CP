/*
The 4th Universal Cup. Stage 18: Grand Prix of Hongō
K. Keep or Gamble
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
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
const int MAXN = 1e7;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int u, t, p, c; cin >> u >> t >> p >> c;

    vector<int> latest_use(u + 1), last_go_t(t + 1, -1);
    for(int i = 0; i <= u; i++) {
        int l = -1, r = t;
        while(l != r) {
            int m = (l + r + 1) / 2;
            ll s = (u - i) * 2 + (t - m) - 1LL * c * (i * 2 + m);
            if(s > 0) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        latest_use[i] = l;
        if(l >= 0) last_go_t[l] = i;
    }

    // cout << "lu : " << latest_use << endl;
    // cout << "lgt : " << last_go_t << endl;

    Z res = 0;
    int cur = -1;
    for(int i = t; i >= 0; i--) {
        cur = max(cur, last_go_t[i]);
        // cout << "i : " << i << " cur : " << cur << endl;
        if(cur >= 0) {
            Z p_front = fact[u + t] * inv_fact[u + t - (i + cur)] * inv_fact[u + t + c] * fact[u + t + c - (i + cur)];
            Z p_comp = inv_fact[u + t] * fact[u + t - (i + cur)] * fact[u] * inv_fact[u - cur] * fact[t] * inv_fact[t - i] * choose(cur + i, cur);
            Z p_reach = p_front * p_comp;
            // cout << "a : " << choose(i + cur, i) << endl;
            // cout << "n : " << i + cur << " k : " << i << endl;
            // cout << "pr : " << p_reach << endl;
            //add contrib for last one is a u
            Z u_contrib = p_reach * (u - cur) / (u + t + c - (i + cur)) * ((cur + 1) * 2 + i);
            // cout << "uc : " << u_contrib << endl;
            res += u_contrib;
            if(latest_use[cur] == i) {
                Z t_contrib = p_reach * (t - i) / (u + t + c - (i + cur)) * (cur * 2 + i + 1);
                // cout << "tc : " << t_contrib << endl;
                res += t_contrib;
            }
        }
    }

    cout << res << '\n';

    return 0;
}
