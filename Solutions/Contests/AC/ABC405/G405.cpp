#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//optimize things with Mo's. 

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
const int SN = 500;
const int MAXN = 250000;
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

int a[MAXN];
int cnts[MAXN];
int bcnts[SN];
Z bmults[SN];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
    }

    int l = 0, r = 0;

    for(int i = 0; i < SN; i++) {
        bmults[i] = 1;
    }

    auto add = [&](int i) -> void {
        int val = a[i];
        int b_idx = val / SN;

        bcnts[b_idx]++;
        bmults[b_idx] *= fact[cnts[val]] * inv_fact[cnts[val] + 1];
        cnts[val]++;
    };

    auto rem = [&](int i) -> void {
        int val = a[i];
        int b_idx = val / SN;

        bcnts[b_idx]--;
        bmults[b_idx] *= fact[cnts[val]] * inv_fact[cnts[val] - 1];
        cnts[val]--;
    };

    auto upd_interval = [&](int tl, int tr) -> void {
        while(tl < l) {
            add(--l);
        }
        while(tr > r) {
            add(r++);
        }
        while(tl > l) {
            rem(l++);
        }
        while(tr < r) {
            rem(--r);
        }
    };

    auto query = [&](int x) -> Z {
        int tot_cnt = 0;
        Z res = 1;

        int s = x / SN;

        for(int i = 0; i < s; i++) {
            tot_cnt += bcnts[i];
            res *= bmults[i];
        }

        for(int i = s * SN; i < x; i++) {
            tot_cnt += cnts[i];
            res *= inv_fact[cnts[i]];
        }

        return fact[tot_cnt] * res;

    };

    vector<vector<vector<array<int,4>>>> qs(SN, vector<vector<array<int,4>>>(SN));

    for(int i = 0; i < q; i++) {
        int l, r, x; cin >> l >> r >> x;
        l--, r--, x--;
        qs[l / SN][r / SN].push_back({l, r, x, i});
    }

    vector<Z> res(q);

    for(int i = 0; i < SN; i++) {
        if(i & 1) {
            for(int j = SN - 1; j >= i; j--) {
                for(auto [l, r, x, id] : qs[i][j]) {
                    upd_interval(l, r + 1);
                    res[id] = query(x);
                }
            }
        } else {
            for(int j = i; j < SN; j++) {
                for(auto [l, r, x, id] : qs[i][j]) {
                    upd_interval(l, r + 1);
                    res[id] = query(x);
                }
            }
        }
    }

    for(auto x : res) cout << x << '\n';

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
// const int MAXN = 250000;
// const int SN = 500;
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

// //RECENTLY MODIFIED AND COULD BE UNSTABLE. REMOVE ME WHEN THIS IS WORKING. 

// int a[MAXN]; //array
// vector<array<int,2>> in_block[MAXN]; //for each value i, stores the block_id as well as the counts
// Z mult_upd[SN][SN]; //[block_idx, x_block]
// Z pc[SN][SN][SN]; //precompute the answer for [L, R, X * SN] exluding the initial factorial at the top
// int ps[SN][MAXN]; //prefix sum 
// int pcs[SN][SN]; //prefix, x
// int running_cnt[MAXN], q_idx[MAXN];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     init_fact();

//     int n, q; cin >> n >> q;

//     for(int i = 0; i < n; i++) {    
//         int x; cin >> x;
//         x--;
//         a[i] = x;

//         int block_idx = i / SN;
//         if(in_block[x].empty() || in_block[x].back()[0] != block_idx) {
//             in_block[x].push_back({block_idx, 1});
//         } else {
//             in_block[x].back()[1]++;
//         }
//     }

//     // complete pc
//     for(int i = 0; i < SN; i++) { //iterating over all L
//         //set all mults to 1
//         for(int j = 0; j < SN; j++) for(int k = 0; k < SN; k++) mult_upd[j][k] = 1;

//         //set the initial prefix mults 
//         for(int j = 0; j < MAXN; j++) { //iterate over all values
//             int p = 0, x_block = j / SN;
//             for(auto [block_idx, cnt] : in_block[j]) {
//                 if(block_idx >= i) {
//                     int nx = p + cnt;
//                     mult_upd[block_idx][x_block] *= fact[nx] * inv_fact[p];
//                     p = nx;
//                 }
//             }
//         }

//         //fill in the values for the current l
//         for(int j = 0; j < SN; j++) { // x
//             Z c = 1;
//             for(int k = i; k < SN; k++) { // r
//                 c *= mult_upd[k][j];
//                 pc[i][k][j] = c;
//             }
//         }

//         for(int j = i; j < SN; j++) { //r   
//             for(int k = 1; k < SN; k++) { //x
//                 pc[i][j][k] *= pc[i][j][k-1];
//             }
//         }
//     }

//     //complete ps
//     for(int i = 0; i < MAXN; i++) {
//         for(auto [block_idx, cnt] : in_block[i]) {
//             ps[block_idx][i] = cnt;
//         }
//         for(int j = 1; j < SN; j++) {
//             ps[j][i] += ps[j-1][i];
//         }
//         for(int j = 0; j < SN; j++) {
//             pcs[i / SN][j] += ps[i / SN][j];
//         }
//     }

//     //complete pcs pt 2
//     for(int i = 1; i < SN; i++) {
//         for(int j = 0; j < SN; j++) {
//             pcs[j][i] += pcs[j][i-1];
//         }
//     }

//     auto upd = [&](Z &res, int &cnt, int q, int val, int add) -> void {
//         if(q_idx[val] == q) {
//             running_cnt[val] += add;
//         } else {
//             q_idx[val] = q;
//             running_cnt[val] = add;
//         }

//         cnt += add;
//         int nx = running_cnt[val];
//         res *= fact[nx - add] * inv_fact[nx];
//     };

//     for(int i = 0; i < q; i++) {
//         int l, r, x; cin >> l >> r >> x;
//         l--;
//         x--;
//         if(r - l <= SN * 2) {
//             // cout << "case 1\n";
//             Z res = 1;
//             int cnt = 0;
//             for(int j = l; j < r; j++) {
//                 if(a[j] < x) {
//                     upd(res, cnt, i, a[j], 1);
//                 }
//             }
//             cout << fact[cnt] * res << "\n";
//         } else {
//             // cout << "case 2\n";
//             //these bounds are [l, r)
//             int lup_block = (l + SN - 1) / SN;
//             int rdown_block = r / SN;
//             int xlast = (x - 1) / SN; //

//             Z res = pc[lup_block][rdown_block][xlast];
//             int cnt = pcs[rdown_block][xlast] - (lup_block == 0 ? 0 : pcs[lup_block][xlast]);

//             for(int j = xlast * SN; j < x; j++) {
//                 int add = ps[rdown_block][j] - (lup_block == 0 ? 0 : ps[lup_block][j]);
//                 upd(res, cnt, i, j, add);
//             }

//             for(int j = l; j < lup_block * SN; j++) {
//                 upd(res, cnt, i, a[j], 1);
//             }

//             for(int j = (rdown_block - 1) * SN; j < r; j++) {
//                 upd(res, cnt, i, a[j], 1);
//             }

//             cout << fact[cnt] * res << "\n";

//         }
//     }


//     return 0;
// }

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
