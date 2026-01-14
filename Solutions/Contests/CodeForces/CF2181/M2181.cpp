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

void solve() {
    
    string x, y; cin >> x >> y;
    vector<vector<int>> dp(2, vector<int>(2, 1e9));
    dp[0][0] = 0;
    for(int i = 0; i < x.size(); i++) {
        vector<vector<int>> nx(2, vector<int>(2, 1e9));
        for(int pi = 0; pi < 2; pi++) {
            for(int pj = 0; pj < 2; pj++) {
                for(int ti = 0; ti < 2; ti++) {
                    for(int tj = 0; tj < 2; tj++) {
                        int hx = x[i] == '1';
                        int hy = y[i] == '1';
                        if(ti) hx ^= 1;
                        if(tj) hy ^= 1;

                        if((hx == 0) == (hy == pj)) {
                            nx[hx][hy] = min(nx[hx][hy], dp[pi][pj] + ti + tj);
                        }

                    }
                }
            }
        }

        dp = nx;

    }
    int res = 1e9;
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) res = min(res, dp[i][j]);
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}