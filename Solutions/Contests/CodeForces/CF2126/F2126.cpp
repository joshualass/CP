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
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<array<int,2>>> adj(n);

    ll score = 0;

    for(int i = 1; i < n; i++) {
        int u, v, c; cin >> u >> v >> c;
        u--; v--;
        adj[u].push_back({v, c});
        adj[v].push_back({u ,c});
        score += c;
    }

    vector<int> par(n);
    vector<int> w(n);
    vector<map<int,ll>> cw(n);

    auto dfs = [&](auto self, int i, int p, int pw) -> void {
        par[i] = p;
        w[i] = pw;
        for(auto [c, w] : adj[i]) {
            if(c != p) {
                self(self, c, i, w);
                cw[i][a[c]] += w;
                if(a[i] == a[c]) score -= w;
            }
        }
    };

    dfs(dfs, 0, -1, 0);

    for(int i = 0; i < q; i++) {
        int v, x; cin >> v >> x;
        v--;

        score += cw[v][a[v]];
        score -= cw[v][x];

        if(par[v] != -1) {
            int p = par[v];
            score += cw[p][a[p]];
            cw[p][a[v]] -= w[v];
            cw[p][x] += w[v];
            score -= cw[p][a[p]];
        }

        a[v] = x;

        cout << score << '\n';

    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}