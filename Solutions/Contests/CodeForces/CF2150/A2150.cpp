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
    
    int n, m; cin >> n >> m;
    string s; cin >> s;
    set<int> unvis, black;
    for(int i = 1; i <= (n + m) * 2; i++) unvis.insert(i);

    auto step = [&](int idx, char move) -> int {
        if(move == 'A') {
            idx++;
        } else {
            idx = *unvis.upper_bound(idx);
        }
        return idx;
    };

    auto color = [&](int idx) -> void {
        unvis.erase(idx);
        black.insert(idx);
    };
    
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        color(x);
    }    

    int prev = 1;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            int start = 1;
            int end = step(start, s[0]);
            color(end);
        } else {
            int start = prev;
            int nx = step(start, s[i - 1]);
            prev = nx;
            int end = step(nx, s[i]);
            color(end);
        }
    }

    cout << black.size() << '\n';
    for(int x : black) cout << x << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}