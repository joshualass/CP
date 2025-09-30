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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<array<int,3>> tests;

    for(int n = 2; ; n *= 3) {
        for(int ub = 10; ub <= 100000; ub *= 10000) {
            for(int times = 0; times < 3; times++) {
                int fuzzy_n = min(100000, max(2, n + ((int) (rng() % n) - (n / 2))));
                int k = (fuzzy_n == 2 ? 0 : rng() % (fuzzy_n - 2));
                array<int,3> test = {fuzzy_n, k, ub};
                if(tests.count(test) == 0) {
                    cout << "gen " << fuzzy_n << " " << k << " " << ub << " > $\n";
                    tests.insert(test);
                }
            }
        }
        if(n >= 100000) break;
    }

    return 0;
}
