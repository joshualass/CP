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
const int MAXN = 5000;
Z fact[MAXN + 1], inv_fact[MAXN + 1];
Z bell[MAXN + 1];

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

void init_bell(int n = MAXN) {
    bell[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            bell[i] += choose(i - 1, j) * bell[i - 1 - j];
        }
    }
}

/*
init_fact()
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

array<int,2> solve_slow(int n, string s) {

    array<int,2> res = {};

    auto dfs = [&](auto self, int i, vector<vector<int>> sets) -> void {
        if(i == n) {
            int ok = 1;
            int score = 0;
            for(vector<int> a : sets) {
                set<char> vis;
                for(int x : a) {
                    vis.insert(s[x]);
                    for(int y : a) {
                        if(x != y) {
                            if(abs(x - y) != 1 && s[x] != s[y]) {
                                ok = 0;
                            }
                        }
                    }
                }
                score += sz(vis) * sz(a);
            }
            if(ok) {
                if(score > res[0]) {
                    res = {score, 1};
                } else if(score == res[0]) {
                    res[1]++;
                }
                // if(score == 6) {
                //     cout << "ttfang" << endl;
                //     for(auto a : sets) cout << a << endl;
                // }
            }
            return;
        }
        for(int x = 0; x < sz(sets); x++) {
            auto c = sets;
            c[x].push_back(i);
            self(self, i + 1, c);
        }
        sets.push_back({i});
        self(self, i + 1, sets);
    };

    dfs(dfs, 0, {});
    return res;

}

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    Z res = 1;
    int cur_len = 0;

    array<int,2> cnts = {};

    auto get_dp = [&](int len) -> Z {
        vector<Z> dp(len + 1);
        assert(len != 1);
        dp[0] = 1;
        for(int i = 1; i <= len; i++) {
            if(i >= 2) dp[i] += dp[i-2];
            if(i >= 3) dp[i] += dp[i-3];
        }
        // cout << "len : " << len << " dp[len] : " << dp[len] << endl;
        return dp[len];
    };  

    for(int i = 0; i < n; i++) {
        int same = 1;
        if(i && s[i] != s[i-1]) same = 0;
        if(i + 1 < n && s[i] != s[i+1]) same = 0;

        if(same) {
            cnts[s[i] - '0']++;
            res *= get_dp(cur_len);
            cur_len = 0;
        } else {
            if(i && s[i] == s[i-1]) {
                res *= get_dp(cur_len);
                cur_len = 0;
            }
            cur_len++;
        }
    }

    res *= get_dp(cur_len);
    res *= bell[cnts[0]];
    res *= bell[cnts[1]];

    int score = 2 * n - (cnts[0] + cnts[1]);
    cout << score << " " << res << '\n';
    // auto [slow_score, slow_cnt] = solve_slow(n, s);

    // if(score != slow_score || res.x != slow_cnt) {
    //     // cout << "diff ss : " << slow_score << " sc : " << slow_cnt << endl;
    //     cout << n << endl;
    //     cout << s << endl;
    //     assert(0);
    // }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();
    init_bell();

    // for(int i = 0; i < 10; i++) cout << "i : " << i << " bell[i] : " << bell[i] << endl;

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}