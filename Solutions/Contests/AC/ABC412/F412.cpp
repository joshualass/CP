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

//RECENTLY MODIFIED AND COULD BE UNSTABLE. REMOVE ME WHEN THIS IS WORKING. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c; cin >> n >> c;
    c--;
    vector<int> a(n);
    vector<int> cnts(3002);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i == c) a[i]++;
        cnts[a[i]]++;
    }

    int sum = accumulate(a.begin(), a.end(), 0);

    vector<Z> dp(3002);

    for(int i = min(3001, sum); i >= 2; i--) {

        // cout << "i : " << i << "\n";

        int in_drawer = sum - 1;
        Z p_rem = 1;
        Z p_hit = Z(i - 1) / in_drawer;

        p_rem -= p_hit;

        Z x = 0;

        // cout << "p_hit contrib : " <<  p_hit * (1 + 0) << '\n';

        x += p_hit * (1 + 0);

        for(int j = i + 1; j <= min(3001, sum); j++) {
            p_hit = Z(j) * cnts[j] / in_drawer;
            p_rem -= p_hit;
            // cout << "j : " << j << " hit : " << p_hit << " j : " << j << " cnts[j] " << cnts[j] << " id : " << in_drawer << " contrib : " << p_hit * (1 + dp[j]) << '\n';
            x += p_hit * (1 + dp[j]);
        }

        x += p_rem * (1);

        // cout << "x : " << x << '\n';

        Z sub_p_rem = 1 - p_rem;
        Z ev = x / sub_p_rem;

        dp[i] = ev;

    }

    // cout << "dp : " << dp << '\n';
    // cout << "cnts : " << cnts << '\n';

    cout << dp[a[c]] << '\n';

    return 0;
}
