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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

bool check(vector<ll> a) {
    int n = a.size();
    sort(a.begin(), a.end());

    cout << "a : " << a << endl;

    auto compute_ev = [](vector<ll> a) -> ld {
        ll sum = 0;
        for(int i = 0; i < a.size(); i++) {
            for(int j = i + 1; j < a.size(); j++) {
                sum += abs(a[i] - a[j]);
            }
        }
        ll cnts = a.size() * (a.size() - 1) / 2;
        return ((ld) sum) / cnts;
    };

    ld init_ev = compute_ev(a);

    vector<ld> evs(n);
    for(int i = 0; i < n; i++) {
        auto t = a;
        t.erase(t.begin() + i);
        evs[i] = compute_ev(t);
    }

    ld max_ev = max(*max_element(evs.begin(), evs.end()), init_ev);
    ld med_ev = evs[(n - 1) / 2];
    cout << "MED_EV : " << med_ev << " MAX_EV : " << max_ev << '\n';
    cout << "EVS : " << evs << '\n';
    if(med_ev < max_ev) {
        cout << "a : " << a << '\n';
        return 0;
    }
    return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int n = 3; n <= 10; n++) {
        for(int tc = 0; tc < 1000; tc++) {
            vector<ll> a(n);
            for(int j = 0; j < n; j++) a[j] = rng() % 10;
            if(!check(a)) {
                return 0;
            }
        }
    }

    cout << "ALL TESTS PASSED" << endl;

    return 0;
}
