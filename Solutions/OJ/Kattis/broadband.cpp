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

    int m, n, k, s; cin >> m >> n >> k >> s;
    vector<ld> a;
    for(int i = 0; i < m; i++) {
        ld x; cin >> x;
        a.push_back(x);
    }
    for(int i = 0; i < n; i++) {
        ld x; cin >> x;
        a.push_back(x);
    }

    sort(a.begin(), a.end());
    n = n + m;

    vector<ld> p(n + 1), ps(n + 1);
    for(int i = 0; i < n; i++) {
        p[i + 1] = p[i] + a[i];
    }
    for(int i = 0; i < n; i++) {
        ps[i + 1] = ps[i] + a[i] * a[i];
    }

    // for(int i = 0; i <= n; i++) cout << p[i] << " ";
    // cout << endl;
    // for(int i = 0; i <= n; i++) cout << ps[i] << " ";
    // cout << endl;

    vector<vector<ld>> pc(n + 1, vector<ld>(n + 1)); //precompute everything to make impl easier. 
    ld add = ((ld) 1) * n * ((ld) s) / 2 * ((ld) s) / 2;

    for(int l = 0; l < n; l++) {
        for(int r = l + 2; r <= n; r++) {
            //just do some math and make a nice observation :)
            ld sum = (p[r] - p[l]);
            ld pos = (p[r] - p[l]) / (r - l);
            // cout << "pos : " << pos << endl;
            ld cost = pos * pos * (r - l) - 2 * pos * sum + ps[r] - ps[l];
            // cout << "first : " << pos * pos << " second : " << -2 * pos * sum << " third : " << ps[r] - ps[l] << endl;
            pc[l][r] = cost;
            // cout << "l : " << l << " r : " << r << " cost : " << cost << endl;
        }
    }

    vector dp(n + 1, vector<ld>(k + 1, 1e18));
    dp[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            for(int p = 0; p < i; p++) {
                dp[i][j] = min(dp[i][j], dp[p][j-1] + pc[p][i]);
            }
        }
    }

    cout << fixed << setprecision(10) << add + dp[n][k] << endl;

    return 0;
}
