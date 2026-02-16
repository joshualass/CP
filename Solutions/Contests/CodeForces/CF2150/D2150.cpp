#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<Z> delta(n + 1), deltadelta(n + 1);

    for(int len = 1; len <= n; len++) {
        int rem = n - len;
        int blocks = rem / 2;
        // cout << "len : " << len << endl;
        if(rem & 1) {
            Z total_ways = choose(blocks + len - 1, blocks) * 2;
            if(len == 1) total_ways /= 2;

            Z avg = Z(n - 1) / len;
            Z wcb = total_ways * avg;

            int max_scc = min(len, n - len + 1);

            // cout << "total_ways : " << total_ways << " wcb : " << wcb << endl;
            
            deltadelta[0] += wcb;
            deltadelta[max_scc] -= wcb;

            deltadelta[n-max_scc + 1] -= wcb;
            deltadelta[n] += wcb;

            Z edge_ways = total_ways / 2;
            if(len == 1) edge_ways *= 2;

            delta[0] += edge_ways;
            delta[n - len + 1] -= edge_ways;
            if(len != 1) {
                delta[len - 1] += edge_ways;
                delta[n] -= edge_ways;
            }

        } else {
            //case do not use a block on the edges
            {
                Z total_ways = choose(blocks + len - 1, blocks);
                Z avg = Z(n) / len;
                Z wcb = total_ways * avg;

                int max_scc = min(len, n - len + 1);

                // cout << "no edge block total_ways : " << total_ways << " wcb : " << wcb << endl;
            
                deltadelta[0] += wcb;
                deltadelta[max_scc] -= wcb;

                deltadelta[n-max_scc + 1] -= wcb;
                deltadelta[n] += wcb;
            }

            //case do use a block on the edges 
            if(len != 1 && blocks) {
                blocks --;
                Z total_ways = choose(blocks + len - 1, blocks);
                Z avg = Z(n - 2) / len;
                Z wcb = total_ways * avg;
    
                int max_scc = min(len, n - len + 1);

                // cout << "edge block total_ways : " << total_ways << " wcb : " << wcb << endl;
            
                deltadelta[0] += wcb;
                deltadelta[max_scc] -= wcb;
    
                deltadelta[n-max_scc + 1] -= wcb;
                deltadelta[n] += wcb;

                delta[0] += total_ways;
                delta[n - len + 1] -= total_ways;

                delta[len - 1] += total_ways;
                delta[n] -= total_ways;
            }
        }
    }

    Z res = 0, cur = 0, curr_delta = 0;
    for(int i = 0; i < n; i++) {
        cur += delta[i];
        curr_delta += deltadelta[i];
        cur += curr_delta;
        res += cur * a[i];
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}