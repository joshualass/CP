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
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    int a = k >> n;
    int rem = k - (a << n);
    vector<int> res(1 << n, a);
    
    for(int i = 0; i < rem; i++) {
        int cur = 0;
        for(int j = 0; j < n; j++) {
            if((i >> j) & 1) cur += 1 << (n - 1 - j);
        }
        res[cur]++;
    }

    cout << (k % (1 << n) ? 1 : 0) << '\n';
    for(int i = 0; i < 1 << n; i++) cout << res[i] << " \n"[i == (1 << n) - 1];

    return 0;
}
