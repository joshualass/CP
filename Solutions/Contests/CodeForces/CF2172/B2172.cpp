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

    int n, m, l, x, y; cin >> n >> m >> l >> x >> y;
    vector<array<ll,3>> events;
    for(int i = 0; i < n; i++) {
        int s, t; cin >> s >> t;
        events.push_back({s, 0, t});
    }
    for(int i = 0; i < m; i++) {
        int p; cin >> p;
        events.push_back({p, 1, i});
    }
    vector<ld> res(m);
    ld min_time = 1e18;
    sort(events.begin(), events.end());
    for(auto event : events) {
        // cout << "Event : " << event[0] << " " << event[1] << " " << event[2] << '\n';
        if(event[1] == 0) {
            auto [s, _, t] = event;
            min_time = min(min_time, ((ld) l - t) / y + ((ld) t - s) / x);
            // cout << "upd min_time : " << min_time << endl;
        } else {
            auto [p, _, id] = event;
            res[id] = min(((ld) l - p) / y, min_time);
            // cout << "time : " << res[id] << endl;
        }
    }

    for(auto x : res) cout << fixed << setprecision(10) << x << '\n';

    return 0;
}
