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

/*
Let's try to solve this problem with PIE. 

Define e_i to be the bad condition where vertex i is reachable from Vertex a_i by traversing 1+ edges. i.e. the value at vertex i is one in its subtree. 
Now, we try to do dp on the pie stuff. 

Let dp[i][j] => when looking at node i's subtree, the sum of number of ways to fix a subset of j conditions to be bad and for this subset, the number of ways to do this. 

lolll, once you know to apply pie and know the dp states, the transitions are extremely easy. nice practice ... ._.

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int n; cin >> n;
    vector<vector<int>> ch(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        ch[p].push_back(i);
    }

    auto not_fft = [&](vector<Z> a, vector<Z> b) -> vector<Z> {
        vector<Z> res(a.size() + b.size() - 1);
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < b.size(); j++) {
                res[i + j] += a[i] * b[j];
            }
        }
        return res;
    };

    auto dfs = [&](auto self, int i) -> vector<Z> {

        vector<Z> dp(1, 1);
        for(int c : ch[i]) {
            dp = not_fft(dp, self(self, c));
        }

        vector<Z> res(dp.size() + 1);
        int ss = dp.size() - 1;
        for(int j = 0; j < dp.size(); j++) {
            //case we opt to make node i a 'bad' node
            int choices = ss - j;
            if(choices > 0) {
                res[j + 1] += dp[j] * choices;
            }
            //case we don't opt to make node i a 'bad' node
            res[j] += dp[j];
        }
        return res;
    };

    vector<Z> res = dfs(dfs, 0);
    Z ans = 0;

    // cout << "res : " << res << '\n';

    for(int i = 0; i <= n; i++) {
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

// /*
// dp[j] is # of ways to fill all but j nodes in subtree
// for the current approach for horizontal merging, we take move iz nodes from i subtree and jz nodes from j subtree and count the # of ways to do this.

// Current approach runs in O(n^4). I think this could be optimized by having a better dp state or optimizing the merging somehow. 

// */

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

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
//     vector<vector<int>> adj(n);
//     for(int i = 1; i < n; i++) {
//         int p; cin >> p; 
//         p--;
//         adj[i].push_back(p);
//         adj[p].push_back(i);
//     }

//     vector<vector<Z>> dp(n);

//     auto merge = [&](vector<Z> &a, vector<Z> &b) -> vector<Z> {
//         vector<Z> res(a.size() + b.size() - 1);
//         // for(int i = 0; i < a.size(); i++) {
//         //     for(int j = 0; j < b.size(); j++) {
//         //         // for(int z = 0; z <= min(i, j); z++) {
//         //         //     res[i - z + j - z] += a[i] * b[j] * choose(i, z) * choose(j, z) * fact[i] * inv_fact[i - z] * fact[j] * inv_fact[j - z];
//         //         // }
//         //         for(int iz = 0; iz <= min(i, j); iz++) {
//         //             for(int jz = 0; jz <= min(i, j); jz++) {
//         //                 // res[i - iz + j - jz] += a[i] * b[j] * choose(i, iz) * choose(j, jz) * fact[j] * inv_fact[j - iz] * fact[i] * inv_fact[i - jz];
//         //                 res[i - iz + j - jz] += a[i] * b[j] * fact[i] * inv_fact[iz] * inv_fact[i - iz] * fact[j] * inv_fact[jz] * inv_fact[j - jz] * fact[j] * inv_fact[j - iz] * fact[i] * inv_fact[i - jz];
//         //             }
//         //         }
//         //     }
//         // }
//         for(int i = 0; i < a.size(); i++) {
//             a[i] *= fact[i] * fact[i];
//         }
//         for(int i = 0; i < b.size(); i++) {
//             b[i] *= fact[i] * fact[i];
//         }
//         for(int i = 0; i < a.size(); i++) {
//             for(int j = 0; j < b.size(); j++) {
//                 for(int iz = 0; iz <= min(i, j); iz++) {
//                     for(int jz = 0; jz <= min(i, j); jz++) {
//                         res[i - iz + j - jz] += a[i] * b[j] * inv_fact[iz] * inv_fact[i - iz] * inv_fact[jz] * inv_fact[j - jz] * inv_fact[j - iz] * inv_fact[i - jz];
//                     }
//                 }
//             }
//         }

//         // vector dp(a.size(), vector<Z>(b.size()));
//         // for(int i = 0; i < a.size(); i++) {
//         //     for(int j = 0; j < b.size(); j++) {
//         //         dp[i][j] = a[i] * b[j];
//         //     }
//         // }

//         // for(int i = ((int) a.size()) - 1; i >= 0; i--) {
//         //     for(int j = ((int) b.size()) - 1; j >= 0; j--) {
//         //         if(i && j) {
//         //             dp[i-1][j-1] += dp[i][j] * i * j * i * j;
//         //         }

//         //         res[i + j] += dp[i][j];
//         //         for(int a = 1; a <= min(i, j); a++) {
//         //             res[i - a + j] += dp[i][j] * choose(i, a) * choose(j, a) * fact[a];
//         //         }
//         //         for(int b = 1; b <= min(i, j); b++) {
//         //             res[i + j - b] += dp[i][j] * choose(j, b) * choose(i, b) * fact[b];
//         //         }
//         //     }
//         // }

//         return res;
//     };

//     auto dfs = [&](auto self, int i, int p) -> void {
//         vector<Z> cur(1, 1);
//         for(int c : adj[i]) {
//             if(c != p) {
//                 self(self, c, i);
//                 cur = merge(cur, dp[c]);
//             }
//         }

//         dp[i].resize(cur.size() + 1);
//         for(int j = 0; j < cur.size(); j++) {
//             //fill
//             dp[i][j] += cur[j] * (j + 1);
//             //no fill
//             dp[i][j+1] += cur[j];
//         }

//         // cout << "i : " << i << " dp[i] : " << dp[i] << '\n';

//     };

//     dfs(dfs, 0, -1);

//     cout << dp[0][0] << '\n';

//     return 0;
// }
