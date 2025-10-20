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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    set<array<int,2>> s;
    vector<array<int,2>> e;
    vector<vector<int>> adj(n);
    
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        s.insert({min(u,v), max(u,v)});
        e.push_back({u, v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> deg(n);
    for(int i = 0; i < n; i++) deg[i] = adj[i].size();

    // cout << "deg : " << deg << '\n';

    auto choose = [&](ll n, ll k) -> ll {
        if(k < 0 || k > n) return 0;
        ll res = 1;
        for(int i = 1; i <= k; i++) {
            res *= (n - i + 1);
            res /= i;
        }
        return res;
    };

    ll res = 0;
    int SM = sqrt(m);
    vector<int> tc(n);

    for(int i = 0; i < n; i++) {
        if(adj[i].size() <= SM) {
            for(int l = 0; l < adj[i].size(); l++) {
                for(int r = l + 1; r < adj[i].size(); r++) {
                    int u = adj[i][l], v = adj[i][r];
                    if(s.count({min(u, v), max(u, v)})) {
                        tc[u]++;
                        tc[v]++;
                    }
                }
            }
        } else {
            vector<int> in(n);
            for(int to : adj[i]) in[to] = 1;
            for(auto [u, v] : e) {
                if(in[u] && in[v]) {
                    tc[u]++;
                    tc[v]++;
                }
            }
        }

        ll contrib_here = 0;

        // cout << "i : " << i << " tc : " << tc << '\n';

        for(int to : adj[i]) {
            ll contrib = choose(deg[i] - 1, 3) * (deg[to] - 1) - tc[to] * choose(deg[i] - 2, 2);
            // cout << "to : " << to << " contrib : " << contrib << '\n';
            // cout << "a : " << choose(deg[i] - 1, 3) << " b : " << (deg[to] - 1) << " c : " << tc[to] << " d : " << choose(deg[i] - 2, 2) << '\n';
            contrib_here += contrib;
        }

        // cout << "i : " << i << " ch : " << contrib_here << "\n";
        res += contrib_here;
        for(int to : adj[i]) tc[to] = 0;
    }

    cout << res << '\n';

    return 0;
}
