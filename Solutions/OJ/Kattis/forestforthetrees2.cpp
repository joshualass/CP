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

/*
very unspecific inputs. we don't really know too much about the input constraints 
and we should make sure that no coordinates are 0, 0 lol ig this is specified, but we 
are supposed to assume the trees are at unique coordinates. 
*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, r; cin >> n >> m >> r;
    assert(n && m && r);
    vector<array<int,2>> a(n), b(m);
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : b) for(auto &y : x) cin >> y;
    
    for(auto x : b) assert(abs(x[0]) + abs(x[1]) <= r);
    // for(auto x : b) assert(x[0] || x[1]);

    set<array<int,2>> sa(a.begin(), a.end());
    set<array<int,2>> sb(b.begin(), b.end());
    assert(sa.size() == n);
    assert(sb.size() == m);

    shuffle(a.begin(), a.end(), rng);
    shuffle(b.begin(), b.end(), rng);

    if(sb.count({0,0})) {
        cout << "Impossible\n";
        return 0;
    }

    // map<array<int,2>, int> unvis;
    // vector<array<int,2>> unvis(m);
    // vector<int> vis(m);

    auto check = [&](int base_idx) -> array<int,2> {
        
        int sx = a[base_idx][0] - b[0][0];
        int sy = a[base_idx][1] - b[0][1];

        int vc = 0;
        int ok = 1;

        for(auto [x, y] : a) {
            x -= sx;
            y -= sy;
            if(abs(x) + abs(y) <= r) {
                int idx = lower_bound(b.begin(), b.end(), array<int,2>{x, y}) - b.begin();
                if(idx < n && b[idx] == array<int,2>{x, y}) {
                    vc++;
                } else {
                    ok = 0;
                    break;
                }
            }
        }

        assert(vc <= m);

        if(ok && vc == m) {
            return {sx, sy};
        } else {
            return {INT_MAX, INT_MAX};
        }

    };

    vector<array<int,2>> solns;

    for(int i = 0; i < 4; i++) {
        sort(b.begin(), b.end());
        for(int j = 0; j < n; j++) {
            auto res = check(j);
            if(res[0] != INT_MAX) {
                solns.push_back(res);
            }
        }
        for(int j = 0; j < m; j++) {
            int x = b[j][0], y = b[j][1];
            b[j] = {y, -x};
        }
        if(solns.size() >= 2) break;
    }

    if(solns.empty()) {
        cout << "Impossible\n";
    } else if(solns.size() == 1) {
        cout << solns[0][0] << " " << solns[0][1] << '\n';
    } else {
        cout << "Ambiguous\n";
    }

    return 0;
}
