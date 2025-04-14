#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
also see jiangly's template
https://codeforces.com/contest/1895/submission/231571612
*/
template<class T>
constexpr T power(T a, ll b, T base = 1) {
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            base *= a;
        }
    }
    return base;
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

constexpr int P = 1e9 + 7;
using Z = Mint<P>;
// using Z = double;
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

template<typename T>
struct Matrix {
    static constexpr T base = 0;
    int r, c;
    vector<vector<T>> mat;
    Matrix(vector<vector<T>> _mat) {
        r = _mat.size();
        c = _mat[0].size();
        mat = _mat;
    }
    constexpr Matrix &operator+=(Matrix rhs) & {
        assert(r == rhs.r && c == rhs.c);
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                mat[i][j] += rhs.mat[i][j];
            }
        }
        return *this;
    }
    constexpr Matrix &operator*=(Matrix rhs) & {
        assert(c == rhs.r);
        vector<vector<T>> res(r,vector<T>(rhs.c));
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < rhs.c; j++) {
                for(int k = 0; k < c; k++) {
                    res[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        c = rhs.c;
        mat = res;
        return *this;
    }
    friend constexpr Matrix operator+(Matrix lhs, Matrix rhs) {
        Matrix res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Matrix operator*(Matrix lhs, Matrix rhs) {
        Matrix res = lhs;
        res *= rhs;
        return res;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;

    vector<vector<array<int,2>>> adj(n);
    
    for(int i = 0; i < m; i++) {
        int u, v, t; cin >> u >> v >> t;
        u--; v--;
        adj[u].push_back({v, t});
        adj[v].push_back({u, t});
    }

    vector<vector<Z>> f(n * 5, vector<Z>(n * 5));

    auto get_id = [&](int node, int dist) -> int {
        return node * 5 + dist;
    };

    for(int i = 0; i < n; i++) {
        for(int dist = 4; dist > 0; dist--) {
            f[get_id(i, dist)][get_id(i, dist - 1)] = 1;
        }
        if(i == n - 1) {
            f[get_id(n - 1, 0)][get_id(n - 1, 0)] = 1;
        } else {
            for(auto [to, t] : adj[i]) {
                f[get_id(i, 0)][get_id(to, t - 1)] += Z(1) / adj[i].size();
            }
        }
    }

    vector<vector<Z>> shijag(n * 5, vector<Z>(n * 5));
    shijag[0][0] = 1;

    Matrix<Z> fmat(f), fs(shijag);
    Matrix<Z> res = power<Matrix<Z>>(fmat, k, fs);

    cout << res.mat[0][get_id(n - 1, 0)] << '\n';

    // int n, m, k; cin >> n >> m >> k;

    // vector<vector<array<int,2>>> adj(n);
    // int s = n;

    // for(int i = 0; i < m; i++) {

    //     int u, v, t; cin >> u >> v >> t;
    //     u--; v--;
    //     adj[u].push_back({v, t});
    //     adj[v].push_back({u, t});

    //     s += (t - 1) * 2;

    // }

    // vector<vector<Z>> f(s, vector<Z>(s));

    // int nx = n;

    // for(int i = 0; i < n; i++) {
    //     if(i == n - 1) {
    //         f[n-1][n-1] = 1;
    //     } else {
    //         for(auto [to, len] : adj[i]) {
    //             int c = i;
    //             for(int j = 0; j < len; j++) {
    //                 int tt;
    //                 if(j == len - 1) {
    //                     tt = to;
    //                 } else {
    //                     tt = nx++;
    //                 }
    //                 Z p = (j == 0 ? Z(1) / adj[i].size() : 1);
    //                 f[c][tt] = p;
    //                 c = tt;
    //             }
    //         }
    //     }
    // }

    // vector<vector<Z>> shijag(s, vector<Z>(s));
    // shijag[0][0] = 1;

    // Matrix<Z> matf(f), matshijag(shijag);
    // Matrix<Z> res = power<Matrix<Z>>(matf, k, matshijag);

    // cout << res.mat[0][n-1] << '\n';

    // for(int i = 0; i < s; i++) {
    //     cout << "i : " << i << " val : " << res.mat[0][i] << '\n';
    // }

    return 0;
}
