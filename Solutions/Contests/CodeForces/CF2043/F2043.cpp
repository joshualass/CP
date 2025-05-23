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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
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
vector<Z> fact(MAXN + 1), inv_fact(MAXN + 1);

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

//RECENTLY MODIFIED AND COULD BE UNSTABLE. REMOVE ME WHEN THIS IS WORKING. 
int p[51][100001];
int x[100001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int n, q; cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        int a; cin >> a;
        p[a][i]++;
        x[i] = a;
    }

    for(int i = 0; i <= 50; i++) {
        for(int j = 1; j <= n; j++) {
            p[i][j] += p[i][j-1];
        }
    }

    for(int i = 1; i <= n; i++) x[i] ^= x[i-1];

    vector<pair<array<int,2>,Z>> dp(64), ndp(64); //{{max, poss}, # ways}

    auto add = [&](int t, int m, Z w) -> void {
        // if(w.x) {
        //     cout << "add called t : " << t << " m : " << m << " w : " << w << '\n';
        // }
        if(ndp[t].first[0] < m) {
            ndp[t] = {{m, 0}, 0};
        }
        if(ndp[t].first[0] == m) {
            ndp[t].first[1] = 1;
            ndp[t].second += w;
        }
    };

    for(int i = 0; i < q; i++) {

        int l, r; cin >> l >> r;
        l--;

        dp.assign(64, {{0,0}, 0});
        // cout << "start\n";

        int cx = 0, tot = 0;

        // for(int l = 0; l < 8; l++) {
        //     cout << "i : " << i << " dp[i] : " << dp[l] << '\n';
        // }

        for(int j = 0; j <= 50; j++) {
            int c = p[j][r] - p[j][l];
            tot += c;
            ndp.assign(64, {{0,0}, 0});
            // cout << "after adding j : " << j << " c : " << c << '\n';

            for(int k = 0; k < 64; k++) {
                if(dp[k].first[1]) {

                    int t = (c & 1 ? k ^ j : k);

                    add(t, dp[k].first[0] + c, dp[k].second);

                    if(c) {
                        t ^= j;
                        add(t, dp[k].first[0] + c - 1, dp[k].second * c);
                    }
                }
            }

            // cout << "interm add\n";

            // for(int l = 0; l < 8; l++) {
            //     cout << "i : " << i << " dp[i] : " << ndp[l] << '\n';
            // }

            if(c & 1) cx ^= j;
            if(c) {
                int t = cx ^ j;
                add(t, tot - 1, choose(c, 1));
                if(c > 1) {
                    add(cx, tot - 2, choose(c, 2));
                }
            }

            swap(dp, ndp);

            // cout << "done add\n";

            // for(int l = 0; l < 8; l++) {
            //     cout << "i : " << i << " dp[i] : " << dp[l] << '\n';
            // }
        }

        int t = x[r] ^ x[l];
        auto res = dp[t];
        if(res.first[1]) {
            cout << res.first[0] << " " << res.second << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
