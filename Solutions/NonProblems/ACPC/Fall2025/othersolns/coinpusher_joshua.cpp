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

    int n, m, c; cin >> n >> m >> c;

    vector<set<array<int,2>>> a(c + 1);

    auto push = [&](auto self, int row, int l, int r) -> void {
        while(a[row].upper_bound({r, INT_MAX}) != a[row].begin()) {
            auto it = a[row].upper_bound({r, INT_MAX});
            it--;
            auto [tl, tr] = *it;
            if(tr >= l) {
                a[row].erase(it);
                self(self, row + 1, tl, tr);
            } else {
                break;
            }
        }
        a[row].insert({l, r});
    };

    for(int i = 0; i < c; i++) {
        int w, p; cin >> w >> p;
        int l = p, r = p + w - 1;

        push(push, 0, l, r);
    }

    int res = 0;
    for(int i = 0; i <= c; i++) {
        if(i >= n) res += a[i].size();
    }

    cout << res << '\n';

    return 0;
}
