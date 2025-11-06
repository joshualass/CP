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

    int n, k; cin >> n >> k;

    vector<vector<int>> dis(n * 2 + 1, vector<int>(2, -1));
    queue<array<int,3>> q;

    auto add_q = [&](int p, int t, int phase) -> void {
        if(dis[p][phase] != -1) return;
        dis[p][phase] = t;
        q.push({p, t, phase});
    };

    add_q(1, 0, 0);
    while(q.size()) {
        auto [pumps, time, phase] = q.front();
        q.pop();
        // cout << "pumps : " << pumps << " time : " << time << " phase : " << phase << '\n';
        if(phase == 0) {
            add_q(pumps, time + 1, 1);
        }
        for(int smash = 0; smash <= k && smash < pumps; smash++) {
            int nx = pumps - smash + (pumps - smash) * (phase == 0);
            if(nx <= n * 2) add_q(nx, time + 1, phase);
        }
    }

    cout << dis[n][1] << '\n';

    return 0;
}
