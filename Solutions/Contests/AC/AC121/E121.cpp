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


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p; 
        p--;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }

    vector<vector<Z>> dp(n);

    auto merge = [&](vector<Z> &a, vector<Z> &b) -> vector<Z> {
        vector<Z> res(a.size() + b.size() - 1);
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < b.size(); j++) {
                // for(int z = 0; z <= min(i, j); z++) {
                //     res[i - z + j - z] += a[i] * b[j] * choose(i, z) * choose(j, z) * fact[i] * inv_fact[i - z] * fact[j] * inv_fact[j - z];
                // }
                for(int iz = 0; iz <= min(i, j); iz++) {
                    for(int jz = 0; jz <= min(i, j); jz++) {
                        res[i - iz + j - jz] += a[i] * b[j] * choose(i, iz) * choose(j, jz) * fact[j] * inv_fact[j - iz] * fact[i] * inv_fact[i - jz];
                    }
                }
            }
        }
        return res;
    };

    auto dfs = [&](auto self, int i, int p) -> void {
        vector<Z> cur(1, 1);
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                cur = merge(cur, dp[c]);
            }
        }

        dp[i].resize(cur.size() + 1);
        for(int j = 0; j < cur.size(); j++) {
            //fill
            dp[i][j] += cur[j] * (j + 1);
            //no fill
            dp[i][j+1] += cur[j];
        }

        // cout << "i : " << i << " dp[i] : " << dp[i] << '\n';

    };

    dfs(dfs, 0, -1);

    cout << dp[0][0] << '\n';

    return 0;
}
