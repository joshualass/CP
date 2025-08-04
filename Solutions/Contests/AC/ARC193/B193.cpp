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

    int n; cin >> n;
    string s; cin >> s;
    // array<Z,2> dp = {1, 0};
    // for(int i = 0; i < n; i++) {
    //     array<Z,2> nx = {0,0};
    //     if(s[i] == '0') {
    //         nx = {dp[0] * 2 + dp[1], dp[1]};
    //     } else {
    //         nx = {dp[0] * 3 + dp[1], dp[0] + dp[1]};
    //     }
    //     dp = nx;
    // }
    // array<Z,4> dp = {0, 0, 1, 0};
    // for(int i = 0; i < n; i++) {
    //     array<Z,4> nx;
    //     if(s[i] == '0') {
    //         nx = {dp[0] * 2 + dp[1] + dp[2] + dp[3], dp[1], dp[2], dp[3]};
    //     } else {
    //         nx = {dp[0] * 3 + dp[1] + dp[2] * 2 + dp[3], dp[0] + dp[1], dp[2], dp[2] + dp[3]};
    //     }
    //     dp = nx;
    // }
    array<Z,6> dp = {0, 0, 1, 0, 0, 0};
    for(int i = 0; i < n; i++) {
        array<Z,6> nx = {0, 0, 0, 0, 0, 0};
        if(s[i] == '0') {
            nx[0] += dp[0] * 2;

            nx[0] += dp[1];
            nx[1] += dp[1];

            nx[0] += dp[2];
            nx[2] += dp[2];

            nx[0] += dp[3];
            nx[3] += dp[3];

            nx[0] += dp[4];
            nx[4] += dp[4];

            nx[0] += dp[5];
            nx[5] += dp[5];
        } else {
            nx[0] += dp[0] * 3;
            nx[1] += dp[0];

            nx[0] += dp[1];
            nx[1] += dp[1];

            nx[0] += dp[2] * 2;
            nx[3] += dp[2];
            nx[4] += dp[2];

            nx[0] += dp[3];
            nx[3] += dp[3];

            nx[0] += dp[4] * 2;
            nx[4] += dp[4];
            nx[5] += dp[4];

            nx[0] += dp[5];
            nx[5] += dp[5];
        }
        dp = nx;
    }

    cout << "dp : " << dp << '\n';

    cout << dp[0] + dp[1] << '\n';

    return 0;
}
