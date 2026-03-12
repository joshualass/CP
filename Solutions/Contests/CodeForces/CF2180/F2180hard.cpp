#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
different approach, but still a fun challenge :)

basic dp, but somehow rated 3200
*/

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

constexpr int P = 1e9 + 7;
using Z = Mint<P>;
// using Z = double;

/*
init_fact()
*/

/*
 1
2X0
 3
*/

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

template<typename T>
constexpr Matrix<T> power(Matrix<T> a, ll b, Matrix<T> base) {
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            base *= a;
        }
    }
    return base;
}

void solve() {
    
    ll n, m; cin >> n >> m;
    vector<vector<Z>> start(n * 2 + 1, vector<Z>(n * 2 + 1));
    start[0][0] = 3 * power<Z>(4, n);
    start[1][1] = power<Z>(4, n);

    vector<vector<Z>> dp(n * 2 + 1, vector<Z>(n * 2 + 1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            if(j == 0) {
                //go forward edge case
                dp[i * 2][i * 2] = 3 * power<Z>(4, n + 1 - 2);
                //go forward then right
                for(int k = i + 1; k < n; k++) {
                    Z above = power<Z>(4, i + 1);
                    Z below = power<Z>(4, n - 1 - k);
                    Z ab_contrib = power<Z>(3, (k - i - 1) * 2) * power<Z>(Z(1) / 4, (k - i - 1));
                    Z one_contrib = 2;
                    dp[i * 2][k * 2] = above * below * ab_contrib * one_contrib * 5 / 4;
                    dp[i * 2][k * 2 + 1] = above * below * ab_contrib * one_contrib / 4;
                }
                //drop all the way down
                dp[i * 2][n * 2] = power<Z>(4, i + 1) * power<Z>(3, n + 1 - (i + 1)) * power<Z>(3, n - 1 - i) * power<Z>(Z(1) / 4, n - 1 - i);
            } else {
                //there is a line below, so we can only optionally go forward
                dp[i * 2 + j][i * 2 + j] += 3 * power<Z>(4, n + 1 - 2);
                dp[i * 2 + j][i * 2] = 3 * 2 * power<Z>(4, n + 1 - 2);
            }
        }
    }
    dp[n * 2][n * 2] = power<Z>(4, n + 1);

    Matrix<Z> basemat(start), amat(dp);
    auto res = power<Z>(amat, m, basemat);
    Z bad = 0;
    for(int i = 0; i < n * 2 + 1; i++) {
        for(int j = 0; j < n * 2 + 1; j++) {
            bad += res.mat[i][j];
        }
    }

    cout << power<Z>(4, (n + 1) * (m + 1)) - bad << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

/*
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3

40
784
13048
1072
91072
6259456
21040
7577344
146054130
*/