#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
program takes sum i = 0 - N, N choose i * 2^i operations. We need to compute for each subset, in how many 
arrangements of wires it is a component. To do this, we also compute the number of ways for each subset the number of 
arrangements within this component as well as the number of ways for this component to be connected. To compute a state, 
we look at all the sets of that have the first element connected to every possible subset of the subset and iterate over all the subsets. 
Overall, this is O(3^N). It is the same sol'n as the editorial. 

todo - optimize by subset convolution. 

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

constexpr int P = 998244353;
using Z = Mint<P>;
// using Z = double;
const int MAXN = 1e6 + 1;
vector<Z> fact(MAXN), inv_fact(MAXN), res(MAXN), pows(MAXN);

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

    init_fact();

    int n, m; cin >> n >> m;

    vector<Z> dc(1 << n), comp(1 << n);

    vector<array<int,2>> a(n);
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        a[x-1][0]++;
    }
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        a[x-1][1]++;
    }

    for(int i = 1; i < 1 << n; i++) {
        array<int,2> b = {0,0};
        for(int j = 0; j < n; j++) {
            if((i >> j) & 1) {
                for(int k = 0; k < 2; k++) {
                    b[k] += a[j][k];
                }
            }
        }
        if(b[0] == b[1]) {
            dc[i] = fact[b[0]];
        }
        // cout << "i : " << i << " dc[i] : " << dc[i] << '\n';
    }

    Z res = 0;

    for(int i = 1; i < 1 << n; i++) {
        Z ways = dc[i];
        int t = 31 - __builtin_clz(i);
        int r = i - (1 << t);

        // cout << "i : " << i << " r : " << r << '\n';

        for(int j = r + 1; j; ) {
            --j &= r;
            // cout << "j : " << j << '\n';
            ways -= dc[j] * comp[r ^ j + (1 << t)];
        }
        comp[i] = ways;
        // cout << "i : " << i << " comp[i] : " << comp[i] << '\n';
        array<int,2> b = {0,0};
        for(int j = 0; j < n; j++) {
            if(((i >> j) & 1) == 0) {
                for(int k = 0; k < 2; k++) {
                    b[k] += a[j][k];
                }
            }
        }
        if(b[0] == b[1]) {
            Z contrib = fact[b[0]] * comp[i];
            // if(contrib.x != 0) {
            //     cout << "i : " << i << " comp[i] : " << comp[i] << " inv fact : " << fact[b[0]] << '\n';
            //     cout << "contrib : " << contrib << '\n';
            // }
            res += contrib;
        }
    }

    cout << res * inv_fact[m] << '\n';

    return 0;
}
