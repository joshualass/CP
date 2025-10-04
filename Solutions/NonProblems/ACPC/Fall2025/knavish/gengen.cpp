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

    set<array<int,5>> tests;

    auto add_test = [&](int n, int m, int k, int strat, int op_moves) -> void {
        array<int,5> cand = {n, m, k, strat, op_moves};
        if(tests.count(cand) == 0) {
            tests.insert(cand);
            cout << "gen " << n << " " << m << " " << k << " " << strat << " " << op_moves << " > $\n";
        }
    };

    for(int n = 1; n <= 100000; n *= 10) {
        int fuzz = rng() % 10 - 5;
        int fuzzy_n = max(1, min(100000, n + fuzz));
        int m = 100000 / fuzzy_n;
        for(int k = 1; k <= 100000; k *= 10) {
            int fuzz_k = rng() % 10 - 5;
            int fuzzy_k = max(1, min(fuzzy_n * m, k + fuzz_k));
            add_test(fuzzy_n, m, fuzzy_k, 0, fuzzy_n * m / (rng() % 10 + 1));
            add_test(fuzzy_n, m, fuzzy_k, 0, fuzzy_n * m / (rng() % 10 + 1));
            add_test(fuzzy_n, m, fuzzy_k, 0, fuzzy_n * m / (rng() % 10 + 1));
            add_test(fuzzy_n, m, fuzzy_k, 1, -1);            
        }
    }

    return 0;
}
