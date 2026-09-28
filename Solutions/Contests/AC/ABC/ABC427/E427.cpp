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

    int h, w; cin >> h >> w;
    vector<string> a(h);
    for(auto &x : a) cin >> x;

    queue<array<int,7>> q;
    map<array<int,6>, int> vis;

    auto add_q = [&](int ro, int co, int minvr, int minvc, int maxvr, int maxvc, int step) -> void {
        if(abs(ro) > 12 || abs(co) > 12) return;
        if(vis.count({ro, co, minvr, minvc, maxvr, maxvc})) return;
        vis[{ro, co, minvr, minvc, maxvr, maxvc}] = step;
        q.push({ro, co, minvr, minvc, maxvr, maxvc, step});
    };

    add_q(0, 0, 0, 0, 0, 0, 0);
    vector<array<int,2>> d = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int tr = -1, tc = -1;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(a[i][j] == 'T') {
                tr = i;
                tc = j;
            }
        }
    }

    while(q.size()) {
        auto [ro, co, minvr, minvc, maxvr, maxvc, step] = q.front();
        q.pop();
        // cout << "ro : " << ro << " co : " << co << " step : " << step << '\n';

        int ok = 1;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if(a[i][j] == '#') {
                    int f = i + minvr < 0 || i + maxvr >= h || j + minvc < 0 || j + maxvc >= w;
                    if(!f) ok = 0;
                }
            }
        }

        if(ok) {
            cout << step << "\n";
            return 0;
        }

        for(int i = 0; i < d.size(); i++) {
            int nr = ro + d[i][0], nc = co + d[i][1];
            int nminvr = min(minvr, nr);
            int nminvc = min(minvc, nc);
            int nmaxvr = max(maxvr, nr);
            int nmaxvc = max(maxvc, nc);
            int targ_r = tr - nr, targ_c = tc - nc;
            if(targ_r >= 0 && targ_r < h && targ_c >= 0 && targ_c < w) {
                int f = targ_r + minvr < 0 || targ_r + maxvr >= h || targ_c + minvc < 0 || targ_c + maxvc >= w;
                if(a[targ_r][targ_c] != '#' || f) {
                    add_q(nr, nc, nminvr, nminvc, nmaxvr, nmaxvc, step + 1);
                }
            } else {
                add_q(nr, nc, nminvr, nminvc, nmaxvr, nmaxvc, step + 1);
            }
        }
    }

    cout << "-1\n";

    return 0;
}

/*
7 7
#######
#.....#
#.###.#
#..T#.#
#####.#
......#
#######

*/

/*
#..........#
............
............
............
............
............
.....T......
............
............
............
............
#..........#

............
............
............
............
............
............
............
............
............
............
............
............

*/