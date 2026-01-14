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

    ll n, m, k; cin >> n >> m >> k;
    set<ll> s;
    vector<array<ll,2>> a(n), b(m);

    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i;
        s.insert(a[i][0]);
        s.insert(a[i][0] + k);
    }

    for(int i = 0; i < m; i++) {
        cin >> b[i][0];
        b[i][1] = i;
        s.insert(b[i][0]);
        s.insert(b[i][0] + k);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    map<ll,int> cm;
    map<int,ll> rcm;

    int p = 0;
    for(ll x : s) {
        cm[x] = p;
        cm[p] = x;
        p++;
    }

    

    return 0;
}
