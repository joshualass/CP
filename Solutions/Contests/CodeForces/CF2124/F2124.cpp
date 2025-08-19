#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
tc
1
6 30
1 2
1 3
1 4
1 5
1 6
2 1
2 3
2 4
2 5
2 6
3 1
3 2
3 4
3 5
3 6
4 2
4 3
4 4
4 5
4 6
5 1
5 3
5 4
5 5
5 6
6 2
6 3
6 4
6 5
6 6

*/

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

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> one_right(n, n);
    vector<vector<int>> bads(n);
    vector<vector<int>> nearest_restriction(n, vector<int>(n, n));
    for(int i = 0; i < m; i++) {
        int idx, x; cin >> idx >> x;
        idx--; x--;
        bads[idx].push_back(x);
        if(idx >= x) {
            one_right[idx - x] = min(one_right[idx - x], idx);
        }
        nearest_restriction[idx][x] = idx;
    }

    for(int i = n - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            nearest_restriction[i][j] = min(nearest_restriction[i][j], nearest_restriction[i+1][j+1]);
        }
    }

    vector good_cnts(n, vector<int>(n + 1));

    auto upd = [&](int idx, int len, vector<int> &cnts, int &cur, int add) -> void {
        for(int x : bads[idx]) {
            if(x < len) {
                int val = (len + (idx - x) % len) % len;
                if(cnts[val]) cur--;
                cnts[val] += add;
                if(cnts[val]) cur++;
            }
        }
    };

    for(int len = 1; len <= n; len++) {
        vector<int> cnts(len);
        int cur = 0;
        for(int i = 0; i + 1 < len; i++) {
            upd(i, len, cnts, cur, 1);
        }
        for(int i = len - 1; i < n; i++) {
            upd(i, len, cnts, cur, 1);
            int bad_cnt = cur;
            if(cnts[(i - (len - 1)) % len] == 0) bad_cnt++;
            good_cnts[i - (len - 1)][i+1] = len - bad_cnt;
            upd(i - (len - 1), len, cnts, cur, -1);
        }
    }

    // cout << "one_right : " << one_right << '\n';
    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " good_cnts[i] : " << good_cnts[i] << '\n';
    // }

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " nr[i] : " << nearest_restriction[i] << '\n';
    // }

    vector dp(n + 1, vector<Z>(n + 1));
    vector<Z> curs(n + 1);
    vector<vector<Z>> curs_p(n + 1, vector<Z>(n + 1));
    dp[0][1] = 1;

    for(int i = 0; i < n; i++) {
        Z free_cnt = accumulate(dp[i].begin(), dp[i].end(), Z(0));
        // cout << "i : " << i << " free : " << free_cnt << " dp[i] : " << dp[i] << '\n';

        for(int j = 1; j <= i; j++) {
            curs[j] += curs_p[i][j];
            if(one_right[i - j] >= i) {
                dp[i][j] += curs[j];
                dp[i][1] -= curs[j];
            }
        }

        for(int j = 1; i + j <= n; j++) {

            int start = min(n, i + j + 1);
            int stop = min(n, nearest_restriction[i][j] + j + 1);

            curs_p[start][j] += dp[i][j];
            curs_p[stop][j] += dp[i][j];

            dp[i][j] += dp[i][j-1];
            if(i + j <= one_right[i]) {
                dp[i+j][j] += dp[i][j];
            }

            dp[i + j][1] += good_cnts[i][i + j] * free_cnt;

        }

    }

    cout << accumulate(dp[n].begin(), dp[n].end(), Z(0)) << '\n';

}

void solve2() {
    int n, m; cin >> n >> m;

    vector<vector<int>> nr_ur(n, vector<int>(n, n));
    vector<vector<int>> rs(n);

    for(int i = 0; i < m; i++) {
        int idx, x; cin >> idx >> x;
        idx--; x--;
        nr_ur[idx][x] = idx;
        rs[idx].push_back(x);
    }

    for(int i = n - 2; i >= 0; i--) {
        for(int j = n - 2; j >= 0; j--) {
            nr_ur[i][j] = min(nr_ur[i][j], nr_ur[i+1][j+1]);
        }
    }

    auto upd = [&](int idx, int len, int add, vector<int> &cnts, int &cnt) -> void {
        for(int x : rs[idx]) {
            if(x < len) {
                int val = (len + (idx - x) % len) % len;
                cnt -= cnts[val] > 0;
                cnts[val] += add;
                cnt += cnts[val] > 0;
            }
        }
    };

    vector<vector<int>> cg(n, vector<int>(n + 1));
    for(int len = 1; len <= n; len++) {
        vector<int> cnts(len);
        int cnt = 0;
        for(int i = 0; i + 1 < len; i++) {
            upd(i, len, 1, cnts, cnt);
        }
        for(int l = 0; l + len <= n; l++) {
            upd(l + len - 1, 1, 1, cnts, cnt);
            int good_cnt = cnt;
            if(cnts[l % len] == 0) good_cnt--;
            cg[l][l + len] = good_cnt;
            upd(l, len, 0, cnts, cnt);
        }
    }

    vector<vector<Z>> dp(n + 1, vector<Z>(n + 1));
    dp[0][1] = 1;
    for(int i = 0; i < n; i++) {
        Z fc = 0;
        for(int j = 1; j <= n; j++) {
            fc += dp[i][j];
            dp[i][j] += dp[i][j-1];
            if(i + j <= n) {

            }
        }


    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();
    // while(casi-->0) solve2();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

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

// void solve() {
    
//     int n, m; cin >> n >> m;

//     vector bad(n, vector<int>(n));
//     for(int i = 0; i < m; i++) {
//         int idx, x; cin >> idx >> x;
//         bad[idx-1][x-1] = 1;
//     }

//     auto check_perm = [&](int idx, int len, int start) -> int {
//         for(int i = idx; i < idx + len; i++) {
//             if(bad[i][(start + i - idx) % len]) return i - idx;
//         }
//         return len;
//     };

//     vector dp(n + 1, vector<Z>(n + 2));

//     dp[0][n + 1] = 1;

//     for(int i = 0; i < n; i++) {

//         Z sum_here = accumulate(dp[i].begin(), dp[i].end(), Z(0));
//         int max_len = check_perm(i, n - i, 0);

//         for(int len = 1; i + len <= n; len++) {
//             for(int start = 0; start < len; start++) {
//                 Z ways_start = sum_here - (dp[i][start]);
                
//                 if(check_perm(i, len, start) == len) {
//                     if(start) {
//                         dp[i+len][n+1] += ways_start;
//                     } else {
//                         dp[i + len][(len - start)] += ways_start;
//                     }

//                 }
//             }
//         }
//         // cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
//         // cout << "norest : " << no_rest[i] << '\n';
//     }

//     cout << accumulate(dp[n].begin(), dp[n].end(), Z(0)) << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

/*
from handmade tcg 


1
17 272
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
1 12
1 13
1 14
1 15
1 16
1 17
2 1
2 3
2 4
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 12
2 13
2 14
2 15
2 16
2 17
3 1
3 2
3 4
3 5
3 6
3 7
3 8
3 9
3 10
3 11
3 12
3 13
3 14
3 15
3 16
3 17
4 1
4 2
4 3
4 5
4 6
4 7
4 8
4 9
4 10
4 11
4 12
4 13
4 14
4 15
4 16
4 17
5 2
5 3
5 4
5 5
5 6
5 7
5 8
5 9
5 10
5 11
5 12
5 13
5 14
5 15
5 16
5 17
6 1
6 3
6 4
6 5
6 6
6 7
6 8
6 9
6 10
6 11
6 12
6 13
6 14
6 15
6 16
6 17
7 1
7 2
7 4
7 5
7 6
7 7
7 8
7 9
7 10
7 11
7 12
7 13
7 14
7 15
7 16
7 17
8 1
8 2
8 3
8 5
8 6
8 7
8 8
8 9
8 10
8 11
8 12
8 13
8 14
8 15
8 16
8 17
9 2
9 3
9 4
9 5
9 6
9 7
9 8
9 9
9 10
9 11
9 12
9 13
9 14
9 15
9 16
9 17
10 1
10 3
10 4
10 5
10 6
10 7
10 8
10 9
10 10
10 11
10 12
10 13
10 14
10 15
10 16
10 17
11 1
11 2
11 4
11 5
11 6
11 7
11 8
11 9
11 10
11 11
11 12
11 13
11 14
11 15
11 16
11 17
12 2
12 3
12 4
12 5
12 6
12 7
12 8
12 9
12 10
12 11
12 12
12 13
12 14
12 15
12 16
12 17
13 1
13 3
13 4
13 5
13 6
13 7
13 8
13 9
13 10
13 11
13 12
13 13
13 14
13 15
13 16
13 17
14 1
14 2
14 4
14 5
14 6
14 7
14 8
14 9
14 10
14 11
14 12
14 13
14 14
14 15
14 16
14 17
15 2
15 3
15 4
15 5
15 6
15 7
15 8
15 9
15 10
15 11
15 12
15 13
15 14
15 15
15 16
15 17
16 1
16 3
16 4
16 5
16 6
16 7
16 8
16 9
16 10
16 11
16 12
16 13
16 14
16 15
16 16
16 17
17 2
17 3
17 4
17 5
17 6
17 7
17 8
17 9
17 10
17 11
17 12
17 13
17 14
17 15
17 16
17 17

*/