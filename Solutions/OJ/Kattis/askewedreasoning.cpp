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

    int n; cin >> n;
    int ok = 1;
    vector<array<int,2>> ch(n);
    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        ch[i] = {l, r};
        if(l == -1 && r != -1) ok = 0;
    }

    if(!ok) {
        cout << "impossible\n";
        return 0;
    }

    vector<deque<int>> dp(n + 1);
    auto dfs = [&](auto self, int i, auto comp) -> void {
        if(ch[i][0] != -1) self(self, ch[i][0], comp);
        if(ch[i][1] != -1) self(self, ch[i][1], comp);

        int lc = ch[i][0] == -1 ? n : ch[i][0];
        int rc = ch[i][1] == -1 ? n : ch[i][1];

        int ls = dp[lc].size(), rs = dp[rc].size();
        if(ls == rs) {
            if(ls) {
                if(comp(dp[rc].front(), i)) {
                    dp[i].push_back(dp[rc].front());
                    dp[i].push_back(i);
                } else {
                    dp[i].push_back(i);
                    dp[i].push_back(dp[rc].front());
                }
                dp[rc].pop_front();
                dp[i].push_back(dp[lc][0]);
                dp[lc].pop_front();
            } else {
                dp[i].push_back(i);
            }
        } else if(ls == rs + 1) {
            if(comp(i, dp[lc].front())) {
                dp[i].push_back(i);
                dp[i].push_back(dp[lc].front());
            } else {
                dp[i].push_back(dp[lc].front());
                dp[i].push_back(i);
            }
            dp[lc].pop_front();
        } else if(ls > rs) {
            int keep = ls - rs;
            deque<int> temp;
            for(int i = keep; i < ls; i++) {
                temp.push_back(dp[lc][i]);
            }
            for(int i = keep; i < ls; i++) dp[lc].pop_back();
            swap(dp[i], dp[lc]);
            swap(dp[lc], temp);
            dp[i].push_back(i);
        } else {
            int keep = rs - ls + 1;
            deque<int> temp;
            for(int i = keep; i < rs; i++) {
                temp.push_back(dp[rc][i]);
            }
            for(int i = keep; i < rs; i++) dp[rc].pop_back();
            swap(dp[i], dp[rc]);
            swap(temp, dp[rc]);
            dp[i].push_back(i);
            dp[i].push_back(dp[lc].front());
            dp[lc].pop_front();
        }

        //alternate the rest, which is the same for all cases y, x, ...
        while(dp[rc].size()) {
            dp[i].push_back(dp[rc].front());
            dp[rc].pop_front();
            dp[i].push_back(dp[lc].front());
            dp[lc].pop_front();
        }

    };

    auto comp_min = [&](int i, int j) -> bool {
        return i < j;
    };

    dfs(dfs, 0, comp_min);

    vector<int> min_res;
    for(int i = 0; i < n; i++) min_res.push_back(dp[0][i]);

    dp[0].clear();

    auto comp_max = [&](int i, int j) -> bool {
        return i > j;
    };

    dfs(dfs, 0, comp_max);

    vector<int> max_res;
    for(int i = 0; i < n; i++) max_res.push_back(dp[0][i]);

    for(int i = 0; i < n; i++) cout << min_res[i] + 1 << " \n"[i == n - 1];
    for(int i = 0; i < n; i++) cout << max_res[i] + 1 << " \n"[i == n - 1];

    // cout << "mn : " << min_res << '\n';
    // cout << "mx : " << max_res << '\n';

    return 0;
}
