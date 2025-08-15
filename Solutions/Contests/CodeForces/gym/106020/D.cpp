#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
nice combo problem that uses tableaux stuff

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int solve_slow(int n, int m) {

    vector<vector<int>> board(n, vector<int>(m));
    
    int res = 0;
    
    auto dfs = [&](auto self, vector<vector<int>> &board, int nx) -> void {
        if(nx == n * m) {
            res++;
            return;
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if((i == 0 || board[i-1][j]) && (j == 0 || board[i][j-1]) && board[i][j] == 0) {
                    // cout << "board : " << board << " push i : " << i << " j : " << j << endl;
                    board[i][j] = 1;
                    self(self, board, nx + 1);
                    board[i][j] = 0;
                }
            }
        }
    };

    dfs(dfs, board, 0);

    return res;

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

Z pc[2026][2026];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // while(1) {
    //     cout << "pick n, m :" << endl;
    //     int n, m; cin >> n >> m;
    //     cout << "ways for n : " << n << " m : " << m << " is " << solve_slow(n, m) << endl;
    // }

    init_fact();

    for(int i = 0; i <= 2025; i++) {
        for(int j = 0; j <= 2025; j++) {
            if(i == 0 || j == 0) {
                pc[i][j] = 1;
            } else {
                pc[i][j] = pc[i-1][j] * inv_fact[i + j - 1] * fact[i + j - 1 - j];
            }
        }
    }

    for(int i = 0; i <= 2025; i++) {
        for(int j = 0; j <= 2025; j++) {
            pc[i][j] *= fact[i * j];
        }
    }

    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 4; j++) {
            // cout << "i : " << i << " j : " << j << " solve_slow(i,j) : " << solve_slow(i, j) << " pc[i][j] : " << pc[i][j] << '\n';
            assert(solve_slow(i, j) == pc[i][j].x);
        }
    }

    int n, m; cin >> n >> m;
    Z res = 0;
    //ways from normal critical point stuff
    {
        for(int i = 1; i < n; i++) {
            for(int j = 1; j < m; j++) {
                /*
                rectangle dimensions
                i x j - upper left
                i x (m - j) - upper right
                (n - i) x j - bottom left
                (n - i) x (m - j) - bottom right
                */

                Z choose_ways = choose(i * j + (n - i) * (m - j), i * j) * choose(i * (m - j) + (n - i) * j, i * (m - j));
                Z hook_ways = pc[i][j] * pc[i][m-j] * pc[n-i][j] * pc[n-i][m-j];
                Z ways_mult = (((i == 0 || i == n) && (j == 0 || j == m)) ? 1 : 2);
                Z total_ways = choose_ways * hook_ways * ways_mult;
                // if(!((i == 0 || i == n) && (j == 0 || j == m))) total_ways *= 2;
                // total_ways *= 2;
                // cout << "i : " << i << " j : " << j << " ways : " << total_ways << '\n';
                // cout << "breakdown choose_ways : " << choose_ways << " hook_ways : " << hook_ways << " ways_mult : " << ways_mult << '\n';

                res += total_ways;

            }
        }
    }
    //generic horizontal
    auto solve_fixed = [&](int h, int w) -> Z {
        vector<Z> dp(w + 1);
        dp[0] = 1;
        for(int i = 1; i <= w; i++) {
            for(int j = 0; j < i; j++) {
                dp[i] += dp[j] * pc[h][i - j];
            }
        }
        return dp[w];
    };

    Z ways = 0;
    if(n == 1 && m == 1) {
        ways = 1;
    } else if(n == 1) {
        ways = 2;
    } else if(m == 1) {
        ways = 2;
    } else {
        ways = 4 * (solve_fixed(n, m) + solve_fixed(m, n));
        ways -= 4 * pc[n][m];
    }

    res += ways;

    cout << res << '\n';

    // cout << "solve slow result : " << solve_slow(n, m) << '\n';

    return 0;
}
