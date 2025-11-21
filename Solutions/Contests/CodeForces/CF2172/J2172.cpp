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

    int n; cin >> n;
    vector<array<int,3>> events; // {height of event, type, index}
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        events.push_back({x, 0, i});
    }

    for(int i = 0; i + 1 < n; i++) {
        int x; cin >> x;
        events.push_back({x, 1, i});
    }

    map<int,array<int,2>> m; //{right endpoint of wall, {size, time}}
    for(int i = 0; i < n; i++) {
        m[i] = {1, 0};
    }

    vector<int> p(n + 1);

    auto cash_in_the_chips = [&](pair<int,array<int,2>> info, int height) -> void {
        // cout << "citc called on right : " << info.first << " size : " << info.second[0] << " time : " << info.second[1] << endl;
        // cout << "height : " << height << endl;
        int wall_idx = info.first;
        auto [size, time] = info.second;
        // cout << "add " << height - time << " to " << wall_idx - size + 1 << " and " << -(height - time) << " to " << wall_idx + 1 << endl;
        p[wall_idx - size + 1] += height - time;
        p[wall_idx + 1] -= height - time;
    };

    sort(events.begin(), events.end());
    for(auto event : events) {
        int height = event[0];
        int index = event[2];
        // cout << "event : " << event[0] << ", " << event[1] << ", " << event[2] << endl;
        if(event[1] == 0) { //removing a block
            auto it = m.lower_bound(index);
            int wall_idx = it->first;
            auto [size, time] = it->second;
            //add to res the previous stuff
            cash_in_the_chips(*it, height);
            assert(size);
            m[wall_idx] = {size - 1, height};
        } else { //removing a wall
            assert(m.count(index));
            auto curr_size = m[index][0];
            auto next_wall = *m.upper_bound(index);
            cash_in_the_chips(*m.find(index), height);
            cash_in_the_chips(next_wall, height);
            m.erase(index);
            m[next_wall.first][0] += curr_size;
            m[next_wall.first][1] = height;
        }
        // cout << "map after\n";
        // for(auto [k, v] : m) {
        //     cout << "right : " << k << " size : " << v[0] << " time : " << v[1] << endl;
        // }
    }

    int cur = 0;
    for(int i = 0; i < n; i++) {
        cur += p[i];
        cout << cur << " \n"[i == n - 1];
    }

    return 0;
}
