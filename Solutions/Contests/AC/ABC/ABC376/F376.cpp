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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<pair<char, int>> a(q);
    for(auto &x : a) {
        cin >> x.first >> x.second;
        x.second--;
    }

    a.insert(a.begin(), {'L', 0});
    vector<int> dp(n, 1e9);
    dp[1] = 0;

    //given that we are moving piece l down to goal position, returns {number of ops, final position of r}
    auto get_ops = [&](int l, int r, int goal) -> array<int,2> {    
        int t = (goal <= l ? goal : goal - n);
        int ops = l - t;
        if(r > l) r -= n;
        int pos = (r + n) % n;
        if(t <= r && r <= l) {
            pos = (t - 1 + n * 2) % n;
            ops += r - (t - 1);
        }
        return {ops, pos};
    };

    // cout << "dp : " << dp << '\n';

    for(int i = 1; i < a.size(); i++) {
        vector<int> ndp(n, 1e9);
        for(int j = 0; j < n; j++) {
            if(j == a[i - 1].second) {
                continue;
            }
            int l, r;
            if(a[i - 1].first == 'L') {
                l = a[i - 1].second;
                r = j;
            } else {
                l = j;
                r = a[i - 1].second;
            }
            if(a[i].first == 'R') {
                swap(l, r);
            }

            // cout << "j : " << j << " l : " << l << " r : " << r << '\n';
            
            //the left hand is the number we are moving
            auto [ops, nx] = get_ops(l, r, a[i].second);
            ndp[nx] = min(ndp[nx], dp[j] + ops);

            //try left hand going the other direction
            auto [ops2, nx2] = get_ops(n - l - 1, n - r - 1, n - a[i].second - 1);
            nx2 = n - nx2 - 1;

            // cout << "ops : " << ops << " nx : " << nx << '\n';
            // cout << "ops2 : " << ops2 << " nx2 : " << nx2 << '\n';

            ndp[nx2] = min(ndp[nx2], dp[j] + ops2);
        }
        swap(dp, ndp);
        // cout << "i : " << i << " dp : " << dp << '\n';
    }

    cout << *min_element(dp.begin(), dp.end()) << '\n';

    return 0;
}
