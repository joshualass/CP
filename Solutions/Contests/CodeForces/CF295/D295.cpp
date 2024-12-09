#include <iostream>
using namespace std;
const long long MOD = 1e9 + 7;

long long dp_increase[2000][2000], dp_decrease[2000][2000];

signed main() {

    int n, m; cin >> n >> m;
    
    long long res = 0;
    for(int i = 0; i < n; i++) {
        long long p = 0, d = 0;
        for(int j = 1; j < m; j++) {
            if(i) d = (dp_increase[i-1][j] + d) % MOD;
            p = (p + d) % MOD;
            dp_increase[i][j] = (p + 1) % MOD;
            res = (dp_increase[i][j] * (m - j) + res) % MOD;
        }
        long long c = 0, s = 0;
        for(int j = m - 1; j > 0; j--) {
            if(i) {
                c = (dp_decrease[i-1][j] + c) % MOD;
            }
            s = (s + c) % MOD;
            dp_decrease[i][j] = s;
            res = (dp_decrease[i][j] + res) % MOD;
            if(i) {
                s = (dp_increase[i-1][j] * (m - j) + s) % MOD;
                c = (dp_increase[i-1][j] * (m - j) + c) % MOD;
            }
        }
    }

    cout << res << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long long long;
// typedef long double ld;
// using namespace std;

// template<class T>
// constexpr T power(T a, long long b) {
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
//     constexpr Mint(long long x): x{norm(x % getMod())} {}

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
//         x = 1long long * x * rhs.x % getMod();
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
//         long long v;
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

// constexpr int P = 1e9 + 7;
// using Z = Mint<P>;

// Z dp_increase[2000][2000], dp_decrease[2000][2000];

// int cntbruteforce(int n, int m, int p) {
//     int cnt = 0;

//     auto isok = [&](int x) -> int {
//         if(x == 0) return 0;
//         int start = 1e9, stop = -1;
//         vector<vector<int>> idxs(n);
//         for(int i = 0; i < n; i++) {
//             for(int j = 0; j < m; j++) {
//                 if((x >> (i * m + j)) & 1) {
//                     idxs[i].push_back(j);
//                 }
//             }
//             int c = idxs[i].size();
//             if(c != 0 && c != 2) return 0;
//             if(c == 0 && start != 1e9 && stop == -1) stop = i - 1;
//             if(c && stop != -1) return 0;
//             if(start == 1e9 && c) start = i;
//         }
//         // cout << "ok to here x : " << x << '\n';
//         if(stop == -1) stop = n - 1;
//         for(int i = start; i <= stop; i++) {
//             int along longok = 1;
//             for(int j = i - 1; j >= start; j--) {
//                 if(idxs[j][0] < idxs[j+1][0] || idxs[j][1] > idxs[j+1][1]) along longok = 0;
//             }
//             for(int j = i + 1; j <= stop; j++) {
//                 if(idxs[j][0] < idxs[j-1][0] || idxs[j][1] > idxs[j-1][1]) along longok = 0;
//             }
//             if(along longok) {
//                 if(p) {
//                     cout << "board\n";
//                     for(int i = 0; i < n; i++) {
//                         for(int j = 0; j < m; j++) {
//                             cout << (x >> (i * m + j) & 1) << " \n"[j == m - 1];
//                         }
//                     }
//                 }
//                 return 1;
//             }
//         }
//         return 0;
//     };  

//     for(int i = 0; i < (1 << (n*m)); i++) {
//         cnt += isok(i);
//     }

//     return cnt;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NUlong long);

//     for(int i = 0; i < 2000; i++) {
//         for(int j = 0; j < 2000; j++) {
//             dp_increase[i][j] = 0;
//             dp_decrease[i][j] = 0;
//         }
//     }

//     int n, m; cin >> n >> m;
    
//     Z res = 0;
//     for(int i = 0; i < n; i++) {
//         Z p = 0, d = 0;
//         // cout << "i : " << i << "\n";
//         for(int j = 1; j < m; j++) {
//             if(i) d += dp_increase[i-1][j];
//             p += d;
//             dp_increase[i][j] = p + 1;
//             res += dp_increase[i][j] * (m - j);
//             // cout << "j : " << j << " dp_increase[i][j] : " << dp_increase[i][j] << '\n';
//         }
//         Z c = 0, s = 0;
//         for(int j = m - 1; j > 0; j--) {
//             if(i) {
//                 c += dp_decrease[i-1][j];
//             }
//             s += c;
//             dp_decrease[i][j] = s;
//             res += dp_decrease[i][j];
//             if(i) {
//                 s += dp_increase[i-1][j] * (m - j);
//                 c += dp_increase[i-1][j] * (m - j);
//             }
//             // cout << "j : " << j << " dp_decrease[i][j] : " << dp_decrease[i][j] << '\n';
//         }
//     }

//     cout << res << '\n';

//     // cout << "combo cnt : " << res << " bf cnt : " << cntbruteforce(n,m,0) << '\n';

//     return 0;
// }