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

    set<array<int,2>> tests;

    for(int n = 2; ; n *= 3) {
        for(int k = 1; k <= 20; k += 3) {
            int fuzzy_n = min(100000, max(1, n + ((int) (rng() % n) - (n / 2))));
            int fuzzy_k = max(1, min(20, k + ((int) rng() % 3) - 1));
            array<int,2> test = {fuzzy_n, fuzzy_k};
            if(tests.count(test) == 0) {
                tests.insert(test);
                cout << "gen " << fuzzy_n << " " << fuzzy_k << " > $\n";
            }
        }
        if(n >= 100000) break;
    }

    for(int max_cnt = 0; max_cnt < 10; max_cnt++) {
        int fuzzy_n = min(100000, max(1, 100000 + ((int) (rng() % 10) - (10 / 2))));
        int fuzzy_k = max(1, min(20, 20 + ((int) rng() % 3) - 1));
        array<int,2> test = {fuzzy_n, fuzzy_k};
        if(tests.count(test) == 0) {
            tests.insert(test);
            cout << "gen " << fuzzy_n << " " << fuzzy_k << " > $\n";
        }
    }

    return 0;
}
