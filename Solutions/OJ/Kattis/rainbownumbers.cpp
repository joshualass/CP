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

    int res = 0;x
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
