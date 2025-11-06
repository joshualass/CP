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
this problem is strangely familiar ...
*/

const int L = 2520;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int l = 1;
    // for(int i = 1; i <= 10; i++) l = lcm(i, l);

    // cout << l << '\n';

    int n, w; cin >> n >> w;
    vector<int> s(n), v(n);
    for(int &x : s) cin >> x;
    for(int &x : v) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(L, 1e9));

    dp[0][0] = v[0];

    for(int i = 0; i < n; i++) {
        priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;
        auto add_q = [&](int time, int cost) -> void {
            if(dp[i][time] > cost) {
                pq.push({cost, time});
                dp[i][time] = cost;
            }
        };
        for(int j = 0; j < L; j++) {
            add_q((j + 1) % L, dp[i][j] + v[i] * ((j + 1) % s[i] == 0) + w);
        }
        while(pq.size()) {
            auto [cost, time] = pq.top();
            pq.pop();
            if(dp[i][time] != cost) continue;
            add_q((time + 1) % L, dp[i][time] + v[i] * (((time + 1) % s[i]) == 0) + w);
        }
        for(int j = 0; j < L; j++) {
            dp[i + 1][(j + 1) % L] = dp[i][j] + (i == n - 1 ? 0 : v[i + 1] * (((j + 1) % s[i + 1]) == 0));
        }
    }

    int res = INT_MAX;
    for(int i = 0; i < L; i++) res = min(res, dp[n][i]);

    cout << res << '\n';

    return 0;
}
