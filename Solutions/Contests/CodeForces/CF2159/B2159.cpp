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

/*
how does one optimize for memory here. O(n sqrt(n)) memory should never fly :'(

solution - do a slightly different approach
*/

void solve() {
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    int tp = 0;

    if(n > m) {
        tp = 1;
        vector<string> b(m);
        for(int j = 0; j < m; j++) {
            for(int i = 0; i < n; i++) {
                b[j].push_back(a[i][j]);
            }
        }
        swap(n, m);
        a = b;
    }

    vector<vector<int>> res(n, vector<int>(m, INT_MAX));
    vector<vector<int>> prev(n, vector<int>(n, -1)), next(n, vector<int>(n, -1));

    for(int col = 0; col < m; col++) {
        vector<int> lo_row(n, INT_MAX);
        for(int lo = 0; lo < n; lo++) {
            for(int hi = lo + 1; hi < n; hi++) {
                int here = INT_MAX;
                if(a[lo][col] == '1' && a[hi][col] == '1') {
                    if(prev[lo][hi] != -1) {
                        here = (hi - lo + 1) * (col - prev[lo][hi] + 1);
                    }
                    int f = -1;
                    for(int nxcol = col + 1; nxcol < m; nxcol++) {
                        if(a[lo][nxcol] == '1' && a[hi][nxcol] == '1') {
                            f = nxcol;
                            break;
                        }
                    }
                    prev[lo][hi] = col;
                    next[lo][hi] = f;
                }
                if(prev[lo][hi] != -1 && next[lo][hi] != -1) {
                    here = min(here, (hi - lo + 1) * (next[lo][hi] - prev[lo][hi] + 1));
                }
                lo_row[hi] = min(lo_row[hi], here);
            }
            for(int hi = lo; hi < n; hi++) res[lo][col] = min(res[lo][col], lo_row[hi]);
        }
    }


    if(tp) {
        vector<vector<int>> b(m);
        for(int j = 0; j < m; j++) {
            for(int i = 0; i < n; i++) {
                b[j].push_back(res[i][j]);
            }
        }
        swap(n, m);
        res = b;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) cout << (res[i][j] == INT_MAX ? 0 : res[i][j]) << " \n"[j == m - 1];
    }

}


// void solve() {
    
//     int n, m; cin >> n >> m;
//     vector<string> a(n);
//     for(auto &x : a) cin >> x;

//     int transpose = 0;

//     if(n > m) {
//         transpose = 1;
//         vector<string> b(m);
//         for(int j = 0; j < m; j++) {
//             for(int i = 0; i < n; i++) {
//                 b[j].push_back(a[i][j]);
//             }
//         }
//         swap(n, m);
//         a = b;
//     }
    
//     // cout << "n : " << n << " m : " << m << endl;
//     // cout << "a" << endl;
//     // for(int i = 0; i < n; i++) cout << a[i] << endl;

//     vector<vector<int>> p(n, vector<int>(n, -1));
//     vector<vector<array<int,4>>> atsize(n * m + 1); // {u, d, l, r}
//     for(int col = m - 1; col >= 0; col--) {
//         for(int i = 0; i < n; i++) {
//             for(int j = i + 1; j < n; j++) {
//                 if(a[i][col] == '1' && a[j][col] == '1') {
//                     if(p[i][j] != -1) {
//                         int nextcol = p[i][j];
//                         int sz = (j - i + 1) * (nextcol - col + 1);
//                         atsize[sz].push_back({i, j, col, nextcol});
//                     }
//                     p[i][j] = col;
//                 }
//             }
//         }
//     }

//     vector<vector<int>> res(n, vector<int>(m));
//     vector<vector<int>> nu(n, vector<int>(m));

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             nu[i][j] = i;
//         }
//     }

//     auto f = [&](int i, int j, int v) -> void {
//         res[i][j] = v;

//         int nx = -1;
//         for(int k = i; k >= 0; k--) {
//             if(res[k][j] == 0) {
//                 nx = k;
//                 break;
//             }
//         }
//         for(int k = i; k < n; k++) {
//             if(nu[k][j] == i) {
//                 nu[k][j] = nx;
//             } else {
//                 break;
//             }
//         }
//     };

//     for(int sz = 0; sz <= n * m; sz++) {
//         for(auto [u, d, l, r] : atsize[sz]) {
//             for(int col = l; col <= r; col++) {
//                 while(nu[d][col] >= u) {
//                     f(nu[d][col], col, sz);
//                 }
//             }
//         }
//     }
    
//     // cout << "make it here3" << endl;

//     if(transpose) {
//         vector<vector<int>> b(m);
//         for(int j = 0; j < m; j++) {
//             for(int i = 0; i < n; i++) {
//                 b[j].push_back(res[i][j]);
//             }
//         }
//         swap(n, m);
//         res = b;
//     }
    
//     // cout << "make it here4" << endl;

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) cout << res[i][j] << " \n"[j == m - 1];
//     }

// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}