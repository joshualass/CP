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

    // ll piv, two_cnt; cin >> piv >> two_cnt;

    // ll phase_one = piv * 1000 + 250000;
    // ll phase_two = 125000 * two_cnt;
    // ll phase_three = 250000 + 1000.0 * 250000 / (piv << two_cnt);

    // cout << phase_one + phase_two + phase_three << '\n';

    //repeat phase one twice!

    int n; cin >> n;
    //make everything in 64\Z

    ll cost = 0;
    vector<array<int,2>> ops;

    auto add_op = [&](int difficulty, int duration) -> void {
        assert(1 <= difficulty && difficulty < 250000);
        assert(1 <= duration && duration <= 1e6);
        if(ops.size() && difficulty > ops.back()[0]) {
            cost += 1000;
        } 
        cost += duration;
        ops.push_back({difficulty, duration});
    };

    for(int i = 1; i <= 63; i++) {
        vector<array<int,2>> temp;
        for(int j = i; j < 250000; j += 64) {
            temp.push_back({j, 1});
        }
        reverse(temp.begin(), temp.end());
        for(auto [diff, dur] : temp) add_op(diff, dur);
    }

    // cout << "cost after phase1 part 1 : " << cost << '\n';

    //make everything in 4096\Z
    for(int i = 64; i < 64 * 64; i += 64) {
        vector<array<int,2>> temp;
        for(int j = i; j < 250000; j += 64 * 64) {
            temp.push_back({j, 64});
        }
        reverse(temp.begin(), temp.end());
        for(auto [diff, dur] : temp) add_op(diff, dur);
    }

    // cout << "cost after phase1 part 2 : " << cost << '\n';

    //we skip phase 2!
    for(int i = 64 * 64; i < 250000; i += 64 * 64) {
        add_op(i, 64 * 64);
    }

    // cout << cost << '\n';

    cout << ops.size() << '\n';
    for(auto [diff, dur] : ops) {
        cout << diff << " " << dur << '\n';
    }

    return 0;
}
