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

void solve(int n) {
    

    Z f = 1;
    for(int i = 1; i <= n; i++) f *= i;
    
    if(n >= 3) f *= n - 2;

    Z nf = 0;
    for(int i = 3; i <= n; i++) {
        if(i == 3) {
            nf = 3;
        } else {
            nf = nf * i - i;
        }
    }

    cout << f + nf << '\n';

}

int solve_slow(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    vector<int> b;
    while(1) {
        for(int x : a) b.push_back(x);
        if(!next_permutation(a.begin(), a.end())) break;
    }
    int res = 0;
    for(int i = 0; i + n <= sz(b); i++) {
        int s = 0;
        for(int j = 0; j < n; j++) s += b[i + j];
        if(s == n * (n + 1) / 2) res++;
    }
    return res;
}

int slow_fact(int n) {
    int res = 1;
    for(int i = 2; i <= n; i++) res *= i;
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int n; cin >> n;
    Z cur_add = 0;

    for(int i = 1; i <= n; i++) {
        Z nx_add = i * (fact[i-1] - 1) + cur_add * i;
        cur_add = nx_add;
        // cout << "i : " << i << " ca : " << cur_add << endl;
    }

    cout << fact[n] + cur_add << '\n';

    // solve(n);

    // for(int i = 1; i <= 8; i++) {
    //     int res = solve_slow(i);
    //     int slow = slow_fact(i);

    //     if(i >= 3) slow *= i - 2;

    //     cout << "i : " << i << " res : " << res << " f : " << slow << " nf : " << res - slow << endl;
    // }

    return 0;
}
