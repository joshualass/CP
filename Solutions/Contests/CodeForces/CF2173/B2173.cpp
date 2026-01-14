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

void solve() {
    
    int n; cin >> n;
    vector<ll> A(n), B(n);
    for(ll &x : A) cin >> x;
    for(ll &x : B) cin >> x;
    ll mx = 0, mn = 0;
    for(int i = 0; i < n; i++) {
        // ll a, b; cin >> a >> b;
        ll a = A[i], b = B[i];
        ll nxmx = max({mx-a, b - mx, mn - a, b - mn});
        ll nxmn = min({mx-a, b - mx, mn - a, b - mn});
        mx = nxmx;
        mn = nxmn;

        // cout << "i : " << i << " mn : " << mn << " mx : " << mx << '\n';
    }

    // cout << "mn : " << mn << " mx : " << mx << '\n';
    cout << mx << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}