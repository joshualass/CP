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

    ll n, d;
    cin >> n >> d;
    string s;
    getline(cin, s);
    getline(cin, s);
    ll low = 0, high = (1ll << (ll) (n * 3));
    ll val = 0;
    for(int i = 2; i < s.size(); i++) {
        if(s[i] == '0') continue;
        val += 1ll << (ll) (n * 3 - i + 1);
    }
    // cout << "LOW HIGH VAL : " << low << " " << val << " " << high << "\n";
    string ans = "";
    for(int i = 0; i < n; i++) {
        ll range = high - low;
        assert(range % 8 == 0);
        ll mid = low + (range / 8) * d;
        if(val < mid) {
            ans.push_back('A');
            high = mid;
        }
        else {
            ans.push_back('B');
            low = mid;
        }
    }
    cout << ans << "\n";

    return 0;
}
