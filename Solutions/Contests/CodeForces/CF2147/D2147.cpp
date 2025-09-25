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

void solve() {
    
    int n; cin >> n;
    map<ll,ll> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x]++;
    }

    ll a = 0, b = 0;
    vector<ll> oc;
    for(auto [val, freq] : m) {
        if(val & 1) {
            oc.push_back(freq);
        }
        a += val / 2 * freq;
        b += val / 2 * freq;
    }
    sort(oc.rbegin(), oc.rend());
    for(int i = 0; i < oc.size(); i++) {
        if(i & 1) {
            b += oc[i];
        } else {
            a += oc[i];
        }
    }

    cout << a << " " << b << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}