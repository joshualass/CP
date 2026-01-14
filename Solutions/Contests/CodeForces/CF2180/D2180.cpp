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
const ll inf = 1e12;

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) {
        cin >> x;
        x *= 4;
    }

    int res = n - 1;

    ll pl = 1, pr = inf;

    for(int i = 1; i < n; i++) {
        //clamp previous one
        ll dist = a[i] - a[i-1];
        pr = min(pr, dist - 1);

        if(pr < pl) {
            res--;
            pl = 1, pr = inf;
        }

        ll nl = max(1LL, dist - pr);
        ll nr = min(dist - 1, dist - pl);

        pl = nl;
        pr = nr;

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}