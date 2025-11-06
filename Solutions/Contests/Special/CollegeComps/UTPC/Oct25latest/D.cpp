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

    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[x] = i;
    }
    // for(int &x : a) cin >> x;

    int cur = 0;
    for(int i = 1; i < n; i++) {
        cur += abs(a[i] - a[i - 1]);
    }

    int res = cur;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int t = cur;
            if(i) t -= abs(a[i] - a[i - 1]);
            t -= abs(a[i + 1] - a[i]);
            if(j > i + 1) t -= abs(a[j] - a[j - 1]);
            if(j + 1 < n) t -= abs(a[j + 1] - a[j]);
            swap(a[i], a[j]);
            if(i) t += abs(a[i] - a[i - 1]);
            t += abs(a[i + 1] - a[i]);
            if(j > i + 1) t += abs(a[j] - a[j - 1]);
            if(j + 1 < n) t += abs(a[j + 1] - a[j]);
            res = min(res, t);
            swap(a[i], a[j]);
        }
    }

    cout << res << '\n';

    return 0;
}
