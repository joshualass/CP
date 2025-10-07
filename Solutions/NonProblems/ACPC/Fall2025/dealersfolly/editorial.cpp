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

    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());

    //erase median k elements
    a.erase(a.begin() + (n - k) / 2, a.begin() + (n - k) / 2 + k);

    ll total = 0;
    n = a.size();
    for(int i = 0; i < a.size(); i++) {
        total += a[i] * (2 * i - (n - 1));
    }

    //print to several decimal places
    cout << fixed << setprecision(10) << ((ld) total) / (1LL * n * (n - 1) / 2) << '\n';

    return 0;
}
