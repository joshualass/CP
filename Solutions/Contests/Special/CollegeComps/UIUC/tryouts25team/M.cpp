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

    auto get = [&](int num) -> array<int,4> {
        array<int,4> res = {};
        for(int i = 3; i >= 0; i--) {
            res[i] = num % 10;
            num /= 10;
        }
        return res;
    };

    auto give = [&](array<int,4> a) -> int {
        int res = 0;
        for(int i = 0; i < 4; i++) {
            res *= 10;
            res += a[i];
        }
        return res;
    };

    auto op = [&](array<int,4> a, int l, int r, int delta) -> array<int,4> {
        for(int i = l; i <= r; i++) {
            a[i] = (a[i] + delta + 10) % 10;
        }
        return a;
    };

    queue<array<int,2>> q;
    vector<int> vis(10000, -1);

    auto add_q = [&](int state, int step) -> void {
        if(vis[state] != -1) return;
        vis[state] = step;
        q.push({state, step});
    };

    add_q(0, 0);
    while(q.size()) {
        auto [state, step] = q.front();
        q.pop();
        // cout << "state : " << state << " step : " << step << '\n';
        auto astate = get(state);
        for(int l = 0; l <= 3; l++) {
            for(int r = l; r <= 3; r++) {
                for(int delta = -1; delta <= 1; delta += 2) {
                    auto nxstate = op(astate, l, r, delta);
                    add_q(give(nxstate), step + 1);
                }
            }
        }
    }

    // cout << "vis : " << vis << '\n';

    int n; cin >> n;
    while(n-->0) {
        int a, b; cin >> a >> b;
        array<int,4> aa = get(a), ab = get(b);
        for(int i = 0; i < 4; i++) {
            aa[i] = (ab[i] - aa[i] + 10) % 10;
        }
        int targ = give(aa);
        // cout << "targ : " << targ << '\n';
        cout << vis[targ] << '\n';
    }

    return 0;
}
