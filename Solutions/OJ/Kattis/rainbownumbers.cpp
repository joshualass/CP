// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// const int MOD = 998244353;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     string L, R; cin >> L >> R;

//     auto get_digit = [&](string &s, int digit_index) -> int {
//         if(digit_index < s.size()) {
//             return s[s.size() - 1 - digit_index] - '0';
//         }
//         return 0;
//     };

//     auto add_mod = [&](int &x, int add) -> void {
//         x += add;
//         if(x >= MOD) x -= MOD;
//     };

//     vector<vector<vector<vector<int>>>> dp(R.size(), vector<vector<vector<int>>>(10, vector<vector<int>>(2, vector<int>(2))));

//     for(int i = R.size() - 1; i >= 0; i--) {
//         for(int j = 0; j < 10; j++) {
//             for(int k = 0; k < 2; k++) {
//                 for(int l = 0; l < 2; l++) {
//                     //iterate over the previous states to compute dp[i][j][k][l]
//                     if(i != R.size() - 1) {
//                         int pi = i + 1;
//                         for(int pj = 0; pj < 10; pj++) {
//                             if(j != pj) {
//                                 for(int pk = 0; pk < 2; pk++) {
//                                     for(int pl = 0; pl < 2; pl++) {
//                                         //make sure number does not get too low
//                                         if(pk == 1 && j < get_digit(L, i)) continue;
//                                         //make sure number does not get too high
//                                         if(pl == 1 && j > get_digit(R, i)) continue;

//                                         int nj = j;
//                                         int nk = pk && j == get_digit(L, i);
//                                         int nl = pl && j == get_digit(R, i);

//                                         if(nk == k && nl == l) {
//                                             cout << "add mod 2 : " << 
//                                             add_mod(dp[i][j][k][l], dp[i+1][pj][pl][pk]);
//                                         }
//                                     }
//                                 }
//                             }
//                         }
//                     }

//                     //handle beginning each number 
//                     //if we start a digit at index i, it must not be larger than R
//                     if(i == R.size() - 1 && j > get_digit(R, i)) continue;
//                     //if we start a digit at index i, it cannot be smaller than L
//                     if(i < L.size() - 1 || i == L.size() - 1 && j < get_digit(L, i)) continue;
//                     //cannot start with a digit with
//                     if(j == 0) continue;

//                     int nk = (i == L.size() - 1 && j == get_digit(L, i));
//                     int nl = (i == R.size() - 1 && j == get_digit(R, i));

//                     if(k == nk && l == nl) {
//                         cout << "add mod i : " << i << " j : " << j << " k : " << l << " l : " << l << endl;
//                         add_mod(dp[i][j][k][l], 1);
//                     }
//                 }
//             }
//         }
//     }

//     int answer = 0;
//     for(int j = 0; j < 10; j++) {
//         for(int k = 0; k < 2; k++) {
//             for(int l = 0; l < 2; l++) {
//                 add_mod(answer, dp[0][j][k][l]);
//             }
//         }
//     }

//     cout << answer << '\n';

//     return 0;
// }


#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef long double ld;
using namespace std;
const int P = 998244353;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string l, r; cin >> l >> r;
    // vector<vector<int>> dp(r.size() + 1, vector<int>(10));
    vector dp(r.size() + 1, vector(10, vector(2, vector<int>(2))));

    auto gd = [&](string &s, int dig) -> int {
        if(dig >= s.size()) return 0;
        return s[s.size() - 1 - dig] - '0';
    };

    for(int i = r.size(); i > 0; i--) {
        for(int j = 0; j < 10; j++) { //previous digit
            for(int tl = 0; tl < 2; tl++) {//still tight on the low digit
                for(int tr = 0; tr < 2; tr++) {//still tight on the high digit
                    for(int nx = 0; nx < 10; nx++) {
                        if(j != nx) { //cannot be equal
                            int ld = gd(l, i - 1);
                            int rd = gd(r, i - 1);
                            if(tl && nx < ld) continue;
                            if(tr && nx > rd) continue;
                            int nl = tl && (nx == ld);
                            int nr = tr && (nx == rd);
                            dp[i - 1][nx][nl][nr] = (dp[i - 1][nx][nl][nr] + dp[i][j][tl][tr]) % P;
                        }
                    }
                }
            }
        }
        //we can also start a number here. 
        for(int j = 1; j < 10; j++) {
            //can start if greater
            if(i < l.size()) continue;
            int ld = gd(l, i - 1);
            int rd = gd(r, i - 1);
            if(i == l.size() && j < ld) continue;
            if(i == r.size() && j > rd) continue;
            int nl = i == l.size() && j == ld;
            int nr = i == r.size() && j == rd;
            dp[i - 1][j][nl][nr] = (dp[i - 1][j][nl][nr] + 1) % P;
        }
    }

    int res = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                res = (res + dp[0][i][j][k]) % P;
            }
        }
    }

    cout << res << '\n';

    return 0;
}
