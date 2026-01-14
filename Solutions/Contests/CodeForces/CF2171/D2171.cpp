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
    set<int> comps;
    vector<array<int,2>> res;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(comps.empty() || x < *comps.begin()) {
            comps.insert(x);
        } else {
            res.push_back({*comps.begin(), x});
            auto it = comps.begin();
            it++;
            while(it != comps.end() && *it < x) {
                res.push_back({*it, x});
                it = comps.erase(it);
            }
        }
    }

    if(comps.size() == 1) {
        cout << "YES\n";
        // for(auto edge : res) {
        //     cout << edge[0] << " " << edge[1] << '\n';
        // }
    } else {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}