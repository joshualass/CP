#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
const int MAXN = 250000;
const int SN = 500;
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

int pcc[SN][MAXN];
Z pc[SN][SN][SN]; //[l, r, x / sqrt(n)]
int a[MAXN];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        pcc[i / SN][x]++;
        a[i] = x;
    }

    for(int i = 0; i < MAXN; i++) {
        for(int j = 1; j < SN; j++) {
            
        }
    }


    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// //ttfang

// const int MAXN = 250000;
// const int SN = 500; //nice
// const int MOD = 998244353;

// int a[SN][MAXN];
// int bm[SN], cnts[MAXN][SN], tc[SN], b[MAXN]; //block mults, cnt of pref numbers, total count of elements in range, array values
// vector<array<int,3>> queries[SN][MAXN];
// int res[MAXN];
// int fact[MAXN + 1], inv_fact[MAXN + 1], inv[MAXN + 1];

// constexpr int power(int a, int b) {
//     int res = 1;
//     for (; b; b /= 2, a = 1LL * a * a % MOD) {
//         if (b % 2) {
//             res = 1LL * res * a % MOD;
//         }
//     }
//     return res;
// }

// int choose(int n, int k) {
//     if(k < 0 || k > n) return 0;
//     return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
// }

// void init_fact(int n = MAXN) {
//     fact[0] = 1;
//     inv_fact[0] = 1;
//     inv[0] = 1;
//     for(int i = 1; i <= n; i++) {
//         fact[i] = 1LL * fact[i-1] * i % MOD;
//     }
//     inv_fact[n] = power(fact[n], MOD - 2);
//     for(int i = n - 1; i >= 1; i--) {
//         inv_fact[i] = 1LL * inv_fact[i+1] * (i + 1) % MOD;
//     }
//     for(int i = 1; i <= n; i++) {
//         inv[i] = 1LL * inv_fact[i] * fact[i-1] % MOD;
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, q; cin >> n >> q;
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         x--;
//         a[i / SN][x]++;
//         b[i] = x;
//     }

//     for(int i = 0; i < q; i++) {
//         int l, r, x; cin >> l >> r >> x;
//         l--, x--;
//         queries[l / SN][x].push_back({l, r, i});
//     }

//     for(int i = 0; i < SN; i++) {
//         //reset bm
//         for(int j = 0; j < SN; j++) {
//             bm[j] = 1;
//         }
        
//         for(int j = 0; j < MAXN; j++) {
//             //add things
//             int c = 0;
//             for(int k = i + 1; k < SN; k++) {
//                 c += a[k][j];
//                 if(c) {
//                     bm[k] = 1LL * bm[k] * inv_fact[c];
//                 }
//                 cnts[]
//             }

//             //query things

//         }


//     }

//     return 0;
// }
