#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
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

constexpr int P = 1e9 + 7;
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

Z ss(ll n, ll a, ll b) {
    vector<Z> F(2, 1);
    for(int i = 2; i < n; i++) {
        F.push_back(1 / F[i - 1] * (a + b / F[i - 2]));
    }
    Z res = 1;
    for(Z x : F) res *= x;
    return res;
}

vector<vector<Z>> matmult(vector<vector<Z>> &a, vector<vector<Z>> &b) {
    int n = a.size();
    vector<vector<Z>> res(n,vector<Z>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
            }
        }
    }
    return res;
}
//use notation of [from][to]
vector<vector<Z>> matexp(vector<vector<Z>> mat, ll pow) {
    int n = mat.size();
    vector<vector<Z>> result(n,vector<Z>(n));
    for(int i = 0; i < 3; i++) result[i][i] = 1;
    while(pow) {
        if(pow & 1) {
            result = matmult(result,mat); //result is the current matrix, mat is the binexp matrix
        }
        mat = matmult(mat,mat);
        pow >>= 1;
    }
    return result;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 1; i <= 20; i++) {
    //     cout << "i : " << i << " res : " << ss(i, 6, 7) << endl;
    // }

    // while(1) {
    //     ll n, a, b; cin >> n >> a >> b;
    //     cout << ss(n, a, b) << endl;
    // }

    ll n, a, b; cin >> n >> a >> b;

    vector<vector<Z>> mat = {
        {0, 0, b},
        {1, 0, a},
        {0, 1, 0},
        // {0, 1, 0, 0},
        // {0, 0, 1, 0},
        // {0, 0, 0, 1},
        // {b, a, 0, 0}
    };

    auto res = matexp(mat, n);

    // for(auto x : res) cout << x << endl;

    Z sum = 0;
    for(int i = 0; i < 3; i++) sum += res[i][0];
    cout << sum << '\n';

    return 0;
}
