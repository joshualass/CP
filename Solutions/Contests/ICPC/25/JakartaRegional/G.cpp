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

int calc_mex(vector<int> a){ 
    sort(a.begin(), a.end());
    int ptr = 0;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] == ptr + 1) ptr ++;
        if(a[i] != ptr) break;
    }
    return ptr + 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int xsum = 0;
    for(int i = 0; i < n; i++) {
        int r, c;
        cin >> r >> c;
        int g = min(__builtin_ctz(r), __builtin_ctz(c)) + 1;
        xsum ^= g;
        // cout << "G : " << g << endl;
    }
    cout << (xsum ? "Kita" : "Kami") << "\n";

    // int m;
    // cin >> m;
    // vector<pair<int, int>> a(m);
    // for(int i = 0; i < m; i++) cin >> a[i].first >> a[i].second;
    // for(int i = 0; i < m; i++) {
    //     a[i].first --, a[i].second --;
    //     n = max(n, a[i].first + 1), n = max(n, a[i].second + 1);
    // }
    // vector g(n, vector<int>(n, -1));
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         vector<int> nxt;
    //         int k = 0;
    //         {
    //             int p2 = 1;
    //             while(p2 * 2 - 1 <= min(i, j)) {
    //                 p2 *= 2; 
    //                 k ++;
    //             }
    //         }
    //         for(int bits = 0; bits < (1 << k); bits++) {
    //             int cg = 0;
    //             for(int b = 0; b < k; b++) {
    //                 if(!(bits & (1 << b))) continue;
    //                 // if(i == 4 && j == 6) cout << "B : " << b << endl;
    //                 for(int ii = 0; ii < (1 << (b + 1)); ii++) {
    //                     for(int jj = 0; jj < (1 << (b + 1)); jj++) {
    //                         if(ii == 0 && jj == 0) continue;
    //                         assert(i - ii >= 0 && j - jj >= 0);
    //                         cg ^= g[i - ii][j - jj];
    //                         // if(i == 4 && j == 6) cout << "CONTR : " << g[i - ii][j - jj] << "\n";
    //                     }
    //                 }
    //             }
    //             // if(i == 4 && j == 6) cout << "CG : " << cg << "\n";
    //             nxt.push_back(cg);
    //         }
    //         // if(i == 4 && j == 6) {
    //         //     cout << "IJ : " << k << " " << i << " " << j << endl;
    //         //     for(int x : nxt) cout << x << " ";
    //         //     cout << "\n";
    //         // }
    //         g[i][j] = calc_mex(nxt);
    //         // cout << "GIJ : " << g[i][j] << "\n";
    //     }
    // }
    // int xsum = 0;
    // for(int i = 0; i < m; i++) {
    //     int r = a[i].first, c = a[i].second;
    //     xsum ^= g[r][c];
    // }
    // cout << (xsum ? "Kita" : "Kami") << "\n";

    // for(int _ = 0; _ < 6; _++) {
    //     for(int i = 0; i < n; i++) {
    //         for(int j = 0; j < n; j++) {
    //             if(g[i][j] & (1 << _)) cout << "1 ";
    //             else cout << "0 ";
    //         }
    //         cout << "\n";
    //     }
    //     cout << "\n";
    // }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) cout << g[i][j] << " ";
    //     cout << "\n";
    // }

    return 0;
}
