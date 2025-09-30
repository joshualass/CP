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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<int,vector<array<int,2>>> m;
    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        m[l].push_back({r, i});
    }

    vector<int> res(n);
    set<array<int,2>> in;

    int cur = 0;
    while(in.size() || m.size()) {
        if(in.empty()) {
            cur = m.begin()->first;
        }
        for(auto [r, id] : m[cur]) {
            in.insert({r, id});
        }
        m.erase(cur);
        auto [r, id] = *in.begin();
        in.erase(in.begin());
        res[id] = cur++;
    }

    for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

    return 0;
}
