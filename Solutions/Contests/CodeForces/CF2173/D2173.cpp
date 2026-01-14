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
const ll inf = 1e18;

void solve() {
    
    ll n, k; cin >> n >> k;
    vector dp(31, vector(31, vector<ll>(2, -inf))); //bit, ops done, there is a 0/1 at this bit, => # of carries. 

    dp[0][0][n & 1] = 0;

    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 31; j++) {
            for(int k = 0; k < 2; k++) {
                //consider the transitions for doing / not doing the operation. 
                //do the operation
                if(j + 1 < 31) {
                    if(k) {
                        int carries = 1;
                        while(n >> (i + carries) & 1) carries++;
                        dp[i + carries][j+1][1] = max(dp[i + carries][j+1][1], dp[i][j][k] + carries);
                    } else {
                        dp[i+1][j+1][(n >> (i + 1)) & 1] = max(dp[i+1][j+1][(n >> (i + 1)) & 1], dp[i][j][k]);
                    }
                }

                //do not do the operation
                dp[i+1][j][(n >> (i + 1)) & 1] = max(dp[i+1][j][(n >> (i + 1)) & 1], dp[i][j][k]);
            }
        }
    }

    // cout << dp[0][0][0] << '\n';
    // cout << dp[1][0][1] << '\n';

    // cout << k << '\n';

    ll res = 0;
    for(int i = 0; i < 31; i++) {
        if(i <= k) {
            res = max(res, dp[30][i][0] + max(0LL, k - i - 1));
            res = max(res, dp[30][i][1] + k - i);
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}