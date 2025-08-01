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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    map<int,vector<int>> m;
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        m[t].push_back(a[i]);
    }

    vector<Z> res(1, 1);

    auto get_dp = [](vector<int> a) -> vector<Z> {
        vector<Z> dp(1, 1);

        for(int x : a) {
            vector<Z> nx(dp.size() + x);
            for(int start_bad_cnt = 0; start_bad_cnt < dp.size(); start_bad_cnt++) {
                for(int add_bad_cnt = 0; add_bad_cnt <= x; add_bad_cnt++) {
                    int left = x - add_bad_cnt;
                    nx[start_bad_cnt + add_bad_cnt] += dp[start_bad_cnt] * inv_fact[add_bad_cnt] * inv_fact[left];
                }
            }
            dp = nx;
        }

        int pc = a.size();
        for(int i = 0; i < dp.size(); i++) {
            dp[i] *= choose(pc, i) * fact[i];
        }
        // cout << "a : " << a << " dp : " << dp << '\n';
        return dp;
    };

    auto merge = [](vector<Z> a, vector<Z> b) -> vector<Z> {
        vector<Z> res(a.size() + b.size() - 1);
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < b.size(); j++) {
                res[i + j] += a[i] * b[j];
            }
        }
        return res;
    };

    for(auto [team, v] : m) {
        res = merge(res, get_dp(v));
    }

    // cout << "res : " << res << '\n';

    Z ans = 0;

    for(int i = 0; i < res.size(); i++) {
        int left = n - i;
        if(i & 1) {
            ans -= res[i] * fact[left];
        } else {
            ans += res[i] * fact[left];
        }
    }

    cout << ans << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<class T>
// constexpr T power(T a, ll b) {
//     T res = 1;
//     for (; b; b /= 2, a *= a) {
//         if (b % 2) {
//             res *= a;
//         }
//     }
//     return res;
// }

// //Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
// template<int P>
// struct Mint {
//     int x;
//     constexpr Mint(): x{} {}
//     constexpr Mint(ll x): x{norm(x % getMod())} {}

//     static int Mod;
//     constexpr static int getMod() {
//         if(P > 0) {
//             return P;
//         } else {
//             return Mod;
//         }
//     }
//     constexpr static void setMod(int Mod_) {
//         Mod = Mod_;
//     }
//     constexpr int norm(int x) const {
//         if(x < 0) {
//             x += getMod();
//         }
//         if(x >= getMod()) { //not sure why this is needed
//             x -= getMod();
//         }
//         return x;
//     }
//     constexpr int val() const {
//         return x;
//     }
//     constexpr Mint operator-() const {
//         Mint res;
//         res.x = norm(getMod() - x);
//         return res;
//     }
//     constexpr Mint inv() const {
//         assert(x != 0);
//         return power(*this, getMod() - 2);
//     }
//     constexpr Mint &operator*=(Mint rhs) & {
//         x = 1LL * x * rhs.x % getMod();
//         return *this;
//     }
//     constexpr Mint &operator+=(Mint rhs) & {
//         x = norm(x + rhs.x);
//         return *this;
//     }
//     constexpr Mint &operator-=(Mint rhs) & {
//         x = norm(x - rhs.x);
//         return *this;
//     }
//     constexpr Mint &operator/=(Mint rhs) & {
//         return *this *= rhs.inv();
//     }
//     friend constexpr Mint operator*(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res *= rhs;
//         return res;
//     }
//     friend constexpr Mint operator+(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res += rhs;
//         return res;
//     }
//     friend constexpr Mint operator-(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res -= rhs;
//         return res;
//     }
//     friend constexpr Mint operator/(Mint lhs, Mint rhs) {
//         Mint res = lhs;
//         res /= rhs;
//         return res;
//     }
//     friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
//         ll v;
//         is >> v;
//         a = Mint(v);
//         return is;
//     }
//     friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
//         return os << a.val();
//     }
//     friend constexpr bool operator==(Mint lhs, Mint rhs) {
//         return lhs.val() == rhs.val();
//     }
//     friend constexpr bool operator!=(Mint lhs, Mint rhs) {
//         return lhs.val() != rhs.val();
//     }
// };

// constexpr int P = 998244353;
// using Z = Mint<P>;
// // using Z = double;
// const int MAXN = 1e6;
// Z fact[MAXN + 1], inv_fact[MAXN + 1];

// Z choose(int n, int k) {
//     if(k < 0 || k > n) return 0;
//     return fact[n] * inv_fact[k] * inv_fact[n-k];
// }

// void init_fact(int n = MAXN) {
//     fact[0] = Z(1);
//     inv_fact[0] = Z(1);
//     for(int i = 1; i <= n; i++) {
//         fact[i] = fact[i-1] * i;
//     }
//     inv_fact[n] = 1 / fact[n];
//     for(int i = n - 1; i >= 1; i--) {
//         inv_fact[i] = inv_fact[i+1] * (i + 1);
//     }
// }

// /*
// init_fact()
// */


// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     init_fact();

//     int n; cin >> n;
//     vector<int> c(n);
//     Z im = 1;
//     for(int &x : c) {
//         cin >> x;
//         im *= inv_fact[x];    
//     }

//     // {team member count, votes needed in team}
//     map<int,array<int,2>> m;
//     for(int i = 0; i < n; i++) {
//         int t; cin >> t;
//         m[t][0]++;
//         m[t][1] += c[i];
//     }

//     vector res(1, vector<Z>(1, 1));

//     auto merge = [&](vector<vector<Z>> &a, int bvc, int bvn) -> vector<vector<Z>> {

//         vector res(a.size() + bvc, vector<Z>(a[0].size() + bvn));
        
//         for(int avc = 0; avc < a.size(); avc++) {
//             for(int avn = 0; avn < a[0].size(); avn++) {
//                 for(int avoteb = 0; avoteb <= min(avc, bvn); avoteb++) {
//                     for(int bvotea = 0; bvotea <= min(bvc, avn); bvotea++) {
//                         res[avc + bvc - (avoteb + bvotea)][avn + bvn - (avoteb + bvotea)] += a[avc][avn] * fact[avc] * inv_fact[avc - avoteb] * fact[bvn] * inv_fact[bvn - avoteb] * inv_fact[avoteb] * fact[bvc] * inv_fact[bvc - bvotea] * fact[avn] * inv_fact[avn - bvotea] * inv_fact[bvotea];
//                     }
//                 }
//             }
//         }
//         return res;
//     };

//     int vcrem = n, vnrem = n;

//     for(auto [k, v] : m) {
//         auto [bvc, bvn] = v;
//         res = merge(res, bvc, bvn);
//         vcrem -= bvc;
//         vnrem -= bvn;
//         // cout << "k : " << k << " bvc : " << bvc << " bvn : " << bvn << " vcrem : " << vcrem << " vnrem : " << vnrem << '\n';
//         while(res.size() > vnrem + 1) res.pop_back();
//         for(auto &x : res) while(x.size() > vcrem + 1) x.pop_back();
//     }

//     cout << im * res[0][0] << '\n';

//     return 0;
// }
