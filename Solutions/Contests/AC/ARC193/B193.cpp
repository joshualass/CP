#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, multiset<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
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

int pc[2][16][4];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    // int n = 1000000;
    string s; cin >> s;
    // string s(n, '1');
    vector<Z> dp(16);

    auto start_dp = [&]() -> void {
        vector<int> m(4);
        if(s[0] == '0') {
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    int here = i + j;
                    m[here] |= 1 << (i * 2 + j);
                }
            }
        } else {
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    for(int k = 0; k < 2; k++) {
                        int here = i + j + k;
                        m[here] |= 1 << (i * 2 + j);
                    }
                }
            }
        }
        for(int i = 0; i < 4; i++) {
            if(m[i]) {
                dp[m[i]] += 1;
            }
        }
    };

    for(int si = 0; si < 2; si++) {
        for(int ways = 1; ways < 16; ways++) {
            for(int bit = 0; bit < 4; bit++) {
                if((ways >> bit) & 1) {
                    int not_end = bit / 2, not_nx = bit & 1;
                    if(si == 0) {
                        for(int j = 0; j < 2; j++) {
                            int here = ((int) (not_nx == 0)) + j;
                            pc[si][ways][here] |= 1 << (not_end * 2 + j);
                        }
                    } else {
                        for(int j = 0; j < 2; j++) {
                            for(int k = 0; k < 2; k++) {
                                int here = ((int) (not_nx == 0)) + j + k;
                                pc[si][ways][here] |= 1 << (not_end * 2 + j);
                            }
                        }
                    }
                }
            }
        }
    }

    auto mid_dp = [&](int ways, int idx, Z v, vector<Z> &nx) -> void {
        int si = s[idx] == '1';
        for(int i = 0; i < 4; i++) {
            if(pc[si][ways][i]) {
                nx[pc[si][ways][i]] += v;
            }
        }
    };

    Z res = 0;

    auto end_dp = [&](int ways, Z v) -> void {
        vector<int> m(4);
        for(int bit = 0; bit < 4; bit++) {
            if((ways >> bit) & 1) {
                int not_end = bit / 2, not_nx = bit & 1;
                if(s[n - 1] == '0') {
                    int here = ((int) (not_end == 0)) + ((int) (not_nx == 0));
                    m[here] = 1;
                } else {
                    for(int k = 0; k < 2; k++) {
                        int here = ((int) (not_end == 0)) + ((int) (not_nx == 0)) + k;
                        m[here] = 1;
                    }
                }
            }
        }
        res += accumulate(m.begin(), m.end(), 0) * v;
    };

    start_dp();

    // cout << "starting dp : " << dp << '\n';

    for(int i = 1; i + 1 < n; i++) {
        vector<Z> nx(16);
        for(int j = 1; j < 16; j++) {
            mid_dp(j, i, dp[j], nx);
        }
        dp = nx;
    }

    for(int j = 1; j < 16; j++) {
        end_dp(j, dp[j]);
    }

    cout << res << '\n';

    return 0;
}
