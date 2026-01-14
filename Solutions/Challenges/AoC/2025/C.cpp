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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        ll l = 0, r = 999'999'999'999LL;
        // cout << "test s : " << s << '\n';
        while(l != r) {
            ll m = (l + r + 1) / 2;
            string t = to_string(m);
            vector<int> dp(13);
            dp[0] = 1;
            int ok = 0;
            for(int j = 0; j < s.size(); j++) {
                for(int k = 11; k >= 0; k--) {
                    if(dp[k]) {
                        if(s[j] > t[k]) {
                            if(k + (s.size() - j) >= 12) ok = 1;
                        } else if(s[j] == t[k]) {
                            dp[k+1] = 1;
                        }
                    }
                }
            }
            if(dp[12]) ok = 1;
            if(ok) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        ll res = l;
        // for(int i = 0; i < s.size(); i++) {
        //     int x = s[i] - '0';
        //     if(mx * 10 + x > res) {
        //         res = mx * 10 + x;
        //     }
        //     mx = max(mx, x);
        // }
        cout << res << '\n';
        ans += res;
    }

    cout << ans << '\n';

    return 0;
}
