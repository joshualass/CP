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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;
    int rev = n * (n + 1) / 2 - k;

    // cout << "rev : " << rev << '\n';

    vector<vector<int>> dp(n + 1, vector<int>(n * (n + 1) / 2 + 1, -1));
    dp[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        for(int nx = 1; nx <= n * (n + 1) / 2; nx++) {
            for(int len = 1; len <= i; len++) {
                int p = nx - len * (len + 1) / 2;
                if(p >= 0 && dp[i - len][p] != -1) {
                    dp[i][nx] = len;
                }
            }
        }
    }

    if(dp[n][rev] == -1) {
        cout << "0\n";
    } else {
        vector<int> lens;
        int a = n, b = rev;
        while(a) {
            int len = dp[a][b];
            a -= len;
            b -= len * (len + 1) / 2;
            lens.push_back(len);
        }
        reverse(lens.begin(), lens.end());

        // cout << "lens : " << lens << '\n';

        int cur = n;
        for(auto len : lens) {
            for(int i = len - 1; i >= 0; i--) cout << cur - i << " ";
            cur -= len;
        }
        cout << '\n';
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}