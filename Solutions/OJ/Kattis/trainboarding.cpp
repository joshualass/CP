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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, p; cin >> n >> l >> p;

    map<int, int> doors;
    for(int i = 0; i < n; i++) doors[i * l + l / 2] = i;
    doors[-1e9] = -1;
    doors[1e9] = -1;

    // cout << "doors : " << doors << '\n';

    int longest_dist = 0;
    map<int,int> cnts;
    for(int i = 0; i < p; i++) {
        int x; cin >> x;
        auto [after_pos, idx] = *doors.upper_bound(x);
        auto [before_pos, before_idx] = (*--doors.upper_bound(x));

        int before_dist = abs(x - before_pos);
        int after_dist = abs(x - after_pos);

        // cout << "x : " << x << " before dist : " << before_dist << " after dist : " << after_dist << '\n';

        if(before_dist < after_dist) {
            cnts[before_idx]++;
        } else {
            cnts[idx]++;
        }
        longest_dist = max(longest_dist, min(after_dist, before_dist));
    }

    cout << longest_dist << '\n';
    int mx_freq = 0;
    for(auto [k, v] : cnts) mx_freq = max(mx_freq, v);
    cout << mx_freq << '\n';


    return 0;
}
