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
const int MAXN = 100000;
const int MAXK = 20;
const int SZ = 1 << MAXK;
const ll inf = 1e18;

ll cnts[MAXK];
ll pc[MAXK][MAXK];
ll pcss[SZ][MAXK];
ll dp[SZ];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    string s; cin >> s;

    //first count alphabet pairwise inversions. 
    //cnts[i][j] => the number of pairs l < r such that a_l = i and a_r = j
    for(int i = n - 1; i >= 0; i--) {
        int val = s[i] - 'a';
        for(int j = 0; j < k; j++) {
            if(j != val) pc[val][j] += cnts[j];
        }
        cnts[val]++;
    }

    // cout << "PC\n";

    // for(int i = 0; i < k; i++) {
    //     for(int j = 0; j < k; j++) {
    //         cout << pc[i][j] << " \n"[j == k - 1];
    //     }
    // }

    for(int bm = (1 << k) - 2; bm >= 0; bm--) {
        int first = __builtin_ctz(~bm);
        // cout << "bm : " << bm << " first : " << first << '\n';
        for(int j = 0; j < k; j++) {
            pcss[bm][j] = pcss[bm ^ (1 << first)][j] + pc[first][j];
        }
    }

    // cout << "PCSS\n";

    // for(int i = 0; i < 1 << k; i++) {
    //     for(int j = 0; j < k; j++) {
    //         cout << pcss[i][j] << " \n"[j == k - 1];
    //     }
    // }

    fill(dp, dp + (1 << k), inf);

    dp[0] = 0;

    for(int i = 1; i < 1 << k; i++) {
        for(int j = 0; j < k; j++) {
            if((i >> j) & 1) {
                dp[i] = min(dp[i], dp[i - (1 << j)] + pcss[i - (1 << j)][j]);
            }
        }
    }

    cout << dp[(1 << k) - 1] << '\n';

    return 0;
}
