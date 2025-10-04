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

    ll a1, h1, a2, h2; cin >> a1 >> h1 >> a2 >> h2;

    ll ttk = h2;
    ll best = LLONG_MAX;
    while(1) {

        // cout << "try ttk : " << ttk << '\n';

        ll health = a2 * ttk + 1;
        ll attack = (h2 + ttk - 1) / ttk;

        ll ops = max(0LL, health - h1) + max(0LL, attack - a1);
        best = min(best, ops);

        if(ttk == 1) break;
        ttk--;
        ll new_attack = (h2 + ttk - 1) / ttk;
        ttk = (h2 + new_attack - 1) / new_attack;
    }

    cout << best << '\n';

    return 0;
}
