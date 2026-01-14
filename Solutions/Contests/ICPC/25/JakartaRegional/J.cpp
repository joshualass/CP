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

    ll n, a, b; cin >> n >> a >> b;
    vector<int> bits;
    // n = (1LL << 60) + (1LL << 57);
    for(ll i = 0; i < 64; i++) {
        bits.push_back((n >> i) & 1);
    }

    int ok = a == b;

    ll one = n, two = n;
    one |= one << 1;
    one &= one << 1;

    two &= two << 1;
    two |= two << 1;

    n <<= 1;

    // cout << "one : " << one << " two : " << two << " n : " << n << '\n';

    ok &= (n == one || n == two);

    cout << (ok ? "YES" : "NO") << '\n';

    return 0;
}
