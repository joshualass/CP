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
    vector<array<int,2>> a(n);
    vector<set<int>> no_succ(n * 2 + 2);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, i};
        no_succ[x].insert(i);
    }

    int res = 0;
    sort(a.begin(), a.end());
    for(auto [val, i] : a) {
        if(no_succ[val-1].lower_bound(i) != no_succ[val-1].begin()) {
            res++;
            no_succ[val-1].erase(--no_succ[val-1].lower_bound(i));
        } else if(no_succ[val+1].lower_bound(i) != no_succ[val+1].begin()) {
            res++;
            no_succ[val+1].erase(--no_succ[val+1].lower_bound(i));
        }
    }

    cout << n - res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}