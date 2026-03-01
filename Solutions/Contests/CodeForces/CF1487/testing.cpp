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

const int AS = 26;
const int debug = 0;

int a[AS];
Z dp1[2][402][2]; //dp1[i][j][k] - (i - current index of the string, j - used j occurrences of bad 1, k - previous character type 0/1)
Z dp2[2][402][402][3]; // dp2[i][j][k][l] - (i - current index of the string, j - used j occurences of bad 1, k - used k occurrences of bad 2, l - previous character 0 / 1 / 2)

Z dp1p[402], dp2p[402][402];
int solve_slowdp1p[402];
int solve_slowdp2p[402][402];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    for(int i = 0; i < AS; i++) cin >> a[i];

    Z ways_0 = AS * power<Z>(AS - 1, (n - 1) / 2) * AS * power<Z>(AS - 1, (n - 2) / 2);

    dp1[0][0][0] = 1;
    dp2[0][0][0][0] = 1;
    int p = 0;

    auto work = [&](int i) -> void {
        int c = p ^ 1;
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k < 2; k++) {
                dp1[c][j][k] = 0;
                if(i == 0) {
                    if(k == 0) {
                        dp1[c][j][k] += (dp1[p][j][0] + dp1[p][j][1]) * (AS - 1);
                    } else {
                        if(j) {
                            dp1[c][j][k] += dp1[p][j - 1][0] + dp1[p][j - 1][1];
                        }
                    }
                } else {
                    if(k == 0) {
                        dp1[c][j][k] += dp1[p][j][0] * (AS - 2);
                        dp1[c][j][k] += dp1[p][j][1] * (AS - 1);
                    } else {
                        if(j) {
                            dp1[c][j][k] += dp1[p][j-1][0];
                        }
                    }
                }
            }
        }
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= n; k++) {
                for(int l = 0; l < 3; l++) {
                    dp2[c][j][k][l] = 0;
                    for(int pl = 0; pl < 3; pl++) {
                        if(i == 0) {
                            if(l == 0) {
                                dp2[c][j][k][l] += dp2[p][j][k][pl] * (AS - 2);
                            } else if(l == 1) {
                                if(j) {
                                    dp2[c][j][k][l] += dp2[p][j-1][k][pl];
                                }
                            } else if(l == 2) {
                                if(k) {
                                    dp2[c][j][k][l] += dp2[p][j][k-1][pl];
                                }
                            }
                        } else {
                            if(l == 0) {
                                if(pl == 0) {
                                    dp2[c][j][k][l] += dp2[p][j][k][pl] * (AS - 3);
                                } else {
                                    dp2[c][j][k][l] += dp2[p][j][k][pl] * (AS - 2);
                                }
                            } else if(l == 1) {
                                if(j) {
                                    if(pl != l) {
                                        dp2[c][j][k][l] += dp2[p][j-1][k][pl];
                                    }
                                }
                            } else {
                                if(k) {
                                    if(pl != l) {
                                        dp2[c][j][k][l] += dp2[p][j][k-1][pl];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        p ^= 1;
    };

    for(int i = 0; i < (n + 1) / 2; i++) work(i);
    for(int i = 0; i < n / 2; i++) work(i);

    int slow_res_0 = 0;
    int slow_res = 0;
    
    if(debug) {
        auto dfs = [&](auto self, vector<int> &cur, vector<int> &cnts) -> void {
            if(cur.size() == n) {
                solve_slowdp1p[cnts[0]]++;
                solve_slowdp2p[cnts[0]][cnts[1]]++;
                int ok = 1;
                for(int i = 0; i < AS; i++) {
                    if(cnts[i] > a[i]) ok = 0;
                }
                slow_res += ok;
                slow_res_0++;
                return;
            }
            for(int i = 0; i < AS; i++) {
                if(sz(cur) >= 2 && i == cur[sz(cur) - 2]) continue;
                cur.push_back(i);
                cnts[i]++;
                self(self, cur, cnts);
                cnts[i]--;
                cur.pop_back();
            }
        };
        vector<int> cur, cnts(AS);
        dfs(dfs, cur, cnts);
    }

    for(int i = n; i >= 0; i--) {
        for(int j = 0; j < 2; j++) {
            dp1p[i] += dp1[p][i][j];
        }
        if(debug) {
            cout << "i : " << i << " dp1p : " << dp1p[i] << " slow (correct?) : " << solve_slowdp1p[i] << endl;
            assert(dp1p[i] == solve_slowdp1p[i]);
        }
        dp1p[i] += dp1p[i+1];
    }

    for(int i = n; i >= 0; i--) {
        for(int j = n; j >= 0; j--) {
            for(int k = 0; k < 3; k++) {
                dp2p[i][j] += dp2[p][i][j][k];
                // cout << "i : " << i << " j : " << j << " k : " << k << " val : " << dp2[p][i][j][k] << endl;
            }
            if(debug) {
                cout << "i : " << i << " j : " << j << " dp2p : " << dp2p[i][j] << " slow (correct?) : " << solve_slowdp2p[i][j] << '\n';
                assert(dp2p[i][j] == solve_slowdp2p[i][j]);
            }
            dp2p[i][j] += dp2p[i+1][j];
            dp2p[i][j] += dp2p[i][j+1];
            dp2p[i][j] -= dp2p[i+1][j+1];
        }
    }

    Z ways_1 = 0;
    for(int i = 0; i < AS; i++) {
        ways_1 += dp1p[a[i] + 1];
    }

    Z ways_2 = 0;
    for(int i = 0; i < AS; i++) {
        for(int j = i + 1; j < AS; j++) {
            Z w = dp2p[a[i] + 1][a[j] + 1];
            // Z ways_slow = get_ways_2_slow(i, j);
            // cout << "w : " << w << " ways_slow : " << ways_slow << '\n';
            // cout << "i : " << i << " j : " << j << " w : " << w << '\n';
            ways_2 += w;
        }
    }

    cerr << "0 : " << ways_0 << " 1 : " << ways_1 << " 2 : " << ways_2 << endl;

    cout << ways_0 - ways_1 + ways_2 << '\n';

    cerr << "solve_slow res : " << slow_res << endl;

    return 0;
}
