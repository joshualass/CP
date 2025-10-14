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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

/*
intution - there are not very many {l, r} pairs
why would I think this - it seems like a lot of the interval just converge and if they don't converge, then this would because we are exhausting a lot of our elements. 

we tested this with some random values.
*/

void solve() {
    
    int n, z; cin >> n >> z;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    // {{l, r}, the index associated with this}
    map<array<int,2>, int> m;
    vector<array<int,2>> rm;
    vector<array<int,20>> bl; //binary lifts on these indices

    auto dfs = [&](auto self, int l, int r) -> int {
        if(m.count({l, r})) return m[{l, r}];
        int id = bl.size();
        m[{l, r}] = id;
        rm.push_back({l, r});
        bl.push_back({});
        auto nx = upper_bound(a.begin() + r + 1, a.end(), a[l] + z);
        if(nx == a.end()) {
            bl[id][0] = -1;
            return id;
        }
        int idx = nx - a.begin();
        bl[id][0] = self(self, r, idx);
        return id;
    };

    for(int i = 0; i + 1 < n; i++) {
        dfs(dfs, i, i + 1);
    }

    auto go = [&](int idx, int d) -> int {
        if(idx == -1) return -1;
        return bl[idx][d];
    };

    for(int d = 1; d < 20; d++) {
        for(int i = 0; i < bl.size(); i++) {
            bl[i][d] = go(go(i, d - 1), d - 1);
        }
    }

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        l--; r--;
        if(l == r) {
            cout << "1\n";
        } else {
            int cur = m[{l, l + 1}];
            int res = 2;
            for(int d = 19; d >= 0; d--) {
                int nx = bl[cur][d];
                if(nx != -1 && rm[nx][1] <= r) {
                    cur = nx;
                    res += 1 << d;
                }
            }
            cout << res << '\n';
        }
    }

}

void test(int n, int len, int z) {
    vector<int> a(n);
    for(int i = 0; i < n; i++) a[i] = rng() % len + 1;
    sort(a.begin(), a.end());
    set<array<int,2>> s;

    auto dfs = [&](auto self, int l, int r) -> void {
        if(s.count({l, r})) return;
        s.insert({l, r});
        auto nx = upper_bound(a.begin(), a.end(), a[l] + z);
        if(nx == a.end()) return;
        int idx = nx - a.begin();
        self(self, r, idx);
    };

    for(int i = 0; i + 1 < n; i++) {
        dfs(dfs, i, i + 1);
    }

    cout << "n : " << n << " len : " << len << " z : " << z << " s size : " << s.size() << " ratio : " << ((ld) s.size()) / n << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int l = 100; l <= 100000; l *= 10) {
    //     for(int r = 2; r <= 10; r++) {
    //         test(10000, l, l / r);
    //     }
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}