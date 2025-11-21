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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    set<int> s;
    for(int i = 0; i < n; i++) {
        int nx = (i + 1) % n;
        s.insert(i);
        pq.push({max(a[i], a[nx]), i, nx});
    }
    ll res = 0;
    while(pq.size()) {
        auto [cost, i, j] = pq.top();
        pq.pop();
        // cout << "cost : " << cost << " i : " << i << " j : " << j << '\n';
        // cout << "a : " << a << '\n';
        if(s.count(i) == 0 || s.count(j) == 0 || cost != max(a[i],a[j])) continue;
        s.erase(j);

        // cout << "add cost : " << cost << '\n';

        res += cost;
        a[i] = max(a[i], a[j]);

        if(s.size() == 1) continue;

        //previous element
        auto it = s.find(i);
        if(it == s.begin()) {
            it = --s.end();
        } else {
            it--;
        }

        // cout << "push prev unvis : " << (*it) << '\n';

        pq.push({max(a[i], a[*it]), i, *it});

        //next element
        it = s.upper_bound(i);
        if(it == s.end()) {
            it = s.begin();
        }
        
        // cout << "push next unvis : " << (*it) << '\n';
        
        pq.push({max(a[i], a[*it]), i, *it});
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