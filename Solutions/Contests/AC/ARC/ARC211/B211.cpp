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

    int x, y, z; cin >> x >> y >> z;
    string sx, sy, sz;
    if(x == y) {
        sx = string(x, '0');
        sy = string(z, '0');
        sz = string(z, '0');
    } else {
        sx = string(y, '0');
        sy = string(z, '1') + string(x, '0');
        sz = string(y, '0') + string(z, '1');
    }

    auto p = [](string x) -> void {
        cout << x.size() << " ";
        for(int i = 0; i < x.size(); i++) cout << x[i] << " \n"[i == x.size() - 1];
    };

    p(sx);
    p(sy);
    p(sz);

    return 0;
}
