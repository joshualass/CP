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
    
    ll n, m; cin >> n >> m;
    vector<array<ll,2>> a(n);
    for(ll i = 0; i < n; i++) {
        ll x; cin >> x;
        a[i] = {x, i};
    }

    vector<array<ll,2>> res;

    sort(a.begin(), a.end());

    if(m == 0) {

        ll sum = 0;
        for(int i = 0; i + 1 < n; i++) sum += a[i][0];
        if(sum < a[n-1][0]) {
            cout << "-1\n";
            return;
        }

        int p = n - 2;
        ll hp = a[n-1][0];
        while(a[p][0] < hp) {
            res.push_back({p, n - 1});
            hp -= a[p][0];
            p--;
        }

        for(int i = 0; i < p; i++) res.push_back({i, i + 1});
        res.push_back({n-1,p});

    } else {
        if(m * 2 > n) {
            cout << "-1\n";
            return;
        }
    
        for(ll i = m; i < n; i++) {
            res.push_back({i, i - m});
        }
    }

    cout << res.size() << '\n';
    for(auto x : res) cout << a[x[0]][1] + 1 << " " << a[x[1]][1] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}