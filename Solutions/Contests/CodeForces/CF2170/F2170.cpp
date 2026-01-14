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

const int Z = 12;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int q; cin >> q;

    vector<vector<array<int,3>>> queries(n);
    for(int qq = 0; qq < q; qq++) {
        int l, r, x; cin >> l >> r >> x;
        l--; r--;
        queries[l].push_back({r, x, qq});
    }

    vector<int> res(q);
    vector dists(Z + 1, vector<int>(1 << Z, n)); //dists[i][j] stores the earliest index such that the number j can be made in i operations

    for(int i = n - 1; i >= 0; i--) {
        //update distances
        dists[0][0] = i;
        for(int dist = 0; dist < Z; dist++) {
            for(int j = 0; j < 1 << Z; j++) {
                dists[dist + 1][j ^ a[i]] = min(dists[dist + 1][j ^ a[i]], dists[dist][j]);
            }
        }

        for(auto [r, x, id] : queries[i]) {
            int best = Z + 1;
            for(int j = 0; j <= Z; j++) {
                if(dists[j][x] <= r) best = min(best, j);
            }
            if(best == Z + 1) best = 0;
            res[id] = best;
        }
    }

    for(int i = 0; i < q; i++) cout << res[i] << " \n"[i == q - 1];

    return 0;
}
