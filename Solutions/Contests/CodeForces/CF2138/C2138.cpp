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
typedef long long ll;
typedef long double ld;
using namespace std;

const int MAXLEN = 200001;

template<int len = 1>
int solve(int n, vector<int> &a, int x, int y) {
    if(n > len) {
        return solve<std::min(len * 2, MAXLEN)>(n, a, x, y);
    }

    bitset<len> dp {};
    dp[0] = 1;
    for(int x : a) dp |= dp << x;
    int f = 1;
    int total = accumulate(a.begin(), a.end(), 0);
    for(int i = 0; i <= n; i++) {
        if(i <= x && total - i <= y && dp[i] == 1) f = 0;
    }
    return a.size() - f;

}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<vector<int>> ch(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        ch[p].push_back(i);
    }

    vector<int> atdc(n);
    int min_depth = n;
    auto dfs = [&](auto self, int i, int d) -> void {
        atdc[d]++;
        for(int c : ch[i]) self(self, c, d + 1);
        if(ch[i].size() == 0) min_depth = min(min_depth, d);
    };

    dfs(dfs, 0, 0);

    vector<int> a;
    for(int i = 0; i <= min_depth; i++) a.push_back(atdc[i]);

    // cout << "min_depth : " << min_depth << '\n';

    cout << solve(n + 1, a, k, n - k) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}