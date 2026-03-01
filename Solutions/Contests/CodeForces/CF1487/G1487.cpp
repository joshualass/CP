#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

/*
idea is pretty straightforward, but somehow spent forever debugging it. 

mentally overestimating a lot of these problems. just solve with PIE ezpz.
*/

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
template<ll P>
struct Mll {
    ll x;
    constexpr Mll(): x{} {}
    constexpr Mll(ll x): x{norm(x % getMod())} {}

    static ll Mod;
    constexpr static ll getMod() {
        if(P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(ll Mod_) {
        Mod = Mod_;
    }
    constexpr ll norm(ll x) const {
        if(x < 0) {
            x += getMod();
        }
        if(x >= getMod()) { //not sure why this is needed
            x -= getMod();
        }
        return x;
    }
    constexpr ll val() const {
        return x;
    }
    constexpr Mll operator-() const {
        Mll res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr Mll inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr Mll &operator*=(Mll rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr Mll &operator+=(Mll rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Mll &operator-=(Mll rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Mll &operator/=(Mll rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr Mll operator*(Mll lhs, Mll rhs) {
        Mll res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Mll operator+(Mll lhs, Mll rhs) {
        Mll res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Mll operator-(Mll lhs, Mll rhs) {
        Mll res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Mll operator/(Mll lhs, Mll rhs) {
        Mll res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Mll &a) {
        ll v;
        is >> v;
        a = Mll(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mll &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(Mll lhs, Mll rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Mll lhs, Mll rhs) {
        return lhs.val() != rhs.val();
    }
};

constexpr ll P = 998244353;
using Z = Mll<P>;
// using Z = double;
const ll MAXN = 1e6;
Z fact[MAXN + 1], inv_fact[MAXN + 1];

Z choose(ll n, ll k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(ll n = MAXN) {
    fact[0] = Z(1);
    inv_fact[0] = Z(1);
    for(ll i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i;
    }
    inv_fact[n] = 1 / fact[n];
    for(ll i = n - 1; i >= 1; i--) {
        inv_fact[i] = inv_fact[i+1] * (i + 1);
    }
}

/*
init_fact()
*/

const ll AS = 26;
const ll debug = 0;

ll a[AS];
Z dp1[2][402][2]; //dp1[i][j][k] - (i - current index of the string, j - used j occurrences of bad 1, k - previous character type 0/1)
Z dp2[2][402][402][3]; // dp2[i][j][k][l] - (i - current index of the string, j - used j occurences of bad 1, k - used k occurrences of bad 2, l - previous character 0 / 1 / 2)

Z dp1p[402], dp2p[402][402];
ll solve_slowdp1p[402];
ll solve_slowdp2p[402][402];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    for(ll i = 0; i < AS; i++) cin >> a[i];

    Z ways_0 = AS * power<Z>(AS - 1, (n - 1) / 2) * AS * power<Z>(AS - 1, (n - 2) / 2);

    dp1[0][0][0] = 1;
    dp2[0][0][0][0] = 1;
    ll p = 0;

    auto work = [&](ll i) -> void {
        ll c = p ^ 1;
        for(ll j = 0; j <= n; j++) {
            for(ll k = 0; k < 2; k++) {
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
        for(ll j = 0; j <= n; j++) {
            for(ll k = 0; k <= n; k++) {
                for(ll l = 0; l < 3; l++) {
                    dp2[c][j][k][l] = 0;
                    for(ll pl = 0; pl < 3; pl++) {
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

    for(ll i = 0; i < (n + 1) / 2; i++) work(i);
    for(ll i = 0; i < n / 2; i++) work(i);

    ll slow_res_0 = 0, slow_res_1 = 0, slow_res_2 = 0;
    ll slow_res = 0;
    
    if(debug) {
        auto dfs = [&](auto self, vector<ll> &cur, vector<ll> &cnts) -> void {
            if(cur.size() == n) {
                solve_slowdp1p[cnts[0]]++;
                solve_slowdp2p[cnts[0]][cnts[1]]++;
                ll ok = 0;
                for(ll i = 0; i < AS; i++) {
                    if(cnts[i] > a[i]) {
                        ok++;
                    }
                }
                slow_res += ok == 0;
                slow_res_0++;
                slow_res_1 += ok;
                slow_res_2 += ok == 2;
                if(ok >= 3) {
                    cout << "wtf cnts : " << cnts << endl;
                    assert(false);
                }
                return;
            }
            for(ll i = 0; i < AS; i++) {
                if(sz(cur) >= 2 && i == cur[sz(cur) - 2]) continue;
                cur.push_back(i);
                cnts[i]++;
                self(self, cur, cnts);
                cnts[i]--;
                cur.pop_back();
            }
        };
        vector<ll> cur, cnts(AS);
        dfs(dfs, cur, cnts);
    }

    for(ll i = n; i >= 0; i--) {
        for(ll j = 0; j < 2; j++) {
            dp1p[i] += dp1[p][i][j];
        }
        if(debug) {
            cout << "i : " << i << " dp1p : " << dp1p[i] << " slow (correct?) : " << solve_slowdp1p[i] << endl;
            assert(dp1p[i] == solve_slowdp1p[i]);
        }
        dp1p[i] += dp1p[i+1];
    }

    for(ll i = n; i >= 0; i--) {
        for(ll j = n; j >= 0; j--) {
            for(ll k = 0; k < 3; k++) {
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
    for(ll i = 0; i < AS; i++) {
        ways_1 += dp1p[a[i] + 1];
    }

    Z ways_2 = 0;
    for(ll i = 0; i < AS; i++) {
        for(ll j = i + 1; j < AS; j++) {
            Z w = dp2p[a[i] + 1][a[j] + 1];
            // Z ways_slow = get_ways_2_slow(i, j);
            // cout << "w : " << w << " ways_slow : " << ways_slow << '\n';
            // cout << "i : " << i << " j : " << j << " w : " << w << '\n';
            ways_2 += w;
        }
    }

    // cerr << "0 : " << ways_0 << " 1 : " << ways_1 << " 2 : " << ways_2 << endl;
    // cerr << "slow 0 : " << slow_res_0 << " slow 1 : " << slow_res_1 << " slow 2 : " << slow_res_2 << endl;

    cout << ways_0 - ways_1 + ways_2 << '\n';

    // cerr << "solve_slow res : " << slow_res << endl;
    // cerr << "test pie on slow stuff : " << slow_res_0 - slow_res_1 + slow_res_2 << endl;

    return 0;
}
