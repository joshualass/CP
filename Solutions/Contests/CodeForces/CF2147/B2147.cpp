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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> res(n * 2, 1);
    int mxe = n, mxo = n;

    if(n & 1) mxe--;
    else mxo--;

    // cout << "mxe : " << mxe << " mxo : " << mxo << '\n';

    int p = 0;
    for(int i = mxe; i >= 2; i -= 2) {
        res[p] = i;
        res[p + i] = i;
        p++;
    }

    // cout << "res even : " << res << '\n';

    res[p] = mxo;
    res[p + mxo] = mxo;

    // cout << "update mxo : " << res << '\n';

    p = mxe + 1;
    // cout << "p : " << p << '\n';
    for(int i = mxo - 2; i >= 3; i -= 2) {
        res[p] = i;
        res[p + i] = i;
        p++;
    }

    if(n == 1) res = {1,1};
    if(n == 2) res = {1,2,1,2};

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}