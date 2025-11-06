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
    for(int &x : a) cin >> x;
    vector<int> pm(n), sm(n);
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            pm[i] = a[i];
        } else {
            pm[i] = max(pm[i-1], a[i]);
        }
    }

    for(int i = n - 1; i >= 0; i--) {
        if(i == n - 1) {
            sm[i] = a[i];
        } else {
            sm[i] = min(sm[i + 1], a[i]);
        }
    }

    // cout << "a : ";
    // for(int x : a) cout << x << " ";
    // cout << '\n';

    // cout << "pm : ";
    // for(int x : pm) cout << x << " ";
    // cout << '\n';

    // cout << "sm : ";
    // for(int x : sm) cout << x << " ";
    // cout << '\n';

    vector<int> res;
    for(int i = 0; i < n; i++) {
        int ok = 1;
        if(i && pm[i - 1] > a[i]) ok = 0;
        if(i != n - 1 && sm[i + 1] < a[i]) ok = 0;
        if(ok) res.push_back(i);
    }

    cout << res.size();
    for(int i = 0; i < min(100, (int) res.size()); i++) cout << " " << a[res[i]];
    cout << '\n';

    return 0;
}
