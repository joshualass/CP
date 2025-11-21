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

    ll n, m, k; cin >> n >> m >> k;
    vector<vector<array<ll,2>>> adj(n);

    for(ll i = 1; i < n; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<ll> b(n);
    for(ll i = 0; i < k; i++) b[i] = 1;

    vector<array<ll,3>> e;
    for(ll i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        e.push_back({u, v, w});
        b[u] = 1;
        b[v] = 1;
    }

    vector<vector<array<ll,2>>> adj2(n);
    vector<int> imp;

    //returns {important node id, dist to node}
    auto dfs = [&](auto self, ll i, ll p) -> array<ll,2> {
        vector<array<ll,2>> ic;
        for(auto [c, w] : adj[i]) {
            if(c != p) {
                auto ch = self(self, c, i);
                if(ch[0] != -1) {
                    ch[1] += w;
                    ic.push_back(ch);
                }
            }
        }
        if(ic.size() >= 2) b[i] = 1;
        if(b[i]) {
            imp.push_back(i);
            for(auto [c, w] : ic) {
                // cout << "add edge between i : " << i << " and j : " << c << " with w : " << w << '\n';
                adj2[i].push_back({c, w});
                adj2[c].push_back({i, w});
            }
            return {i, 0};
        } else {
            if(ic.empty()) {
                return {-1, -1};
            } else {
                return ic[0];
            }
        }
    };

    dfs(dfs, 0, -1);

    for(auto [u, v, w] : e) {
        adj2[u].push_back({v, w});
        adj2[v].push_back({u, w});
        // cout << "add back edge u : " << u << " v : " << v << " w : " << w << '\n';
    }

    swap(adj, adj2);

    vector<ll> dist(n, LLONG_MAX);
    vector<int> vis(n);

    for(int s = 0; s < k; s++) {
        // cout << "dijkstra from s : " << s << '\n';
        for(int x : imp) {
            dist[x] = LLONG_MAX;
            vis[x] = 0;
        }
        priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
        auto push_q = [&](int i, ll d) -> void {
            if(d < dist[i]) {
                pq.push({d, i});
                dist[i] = d;
            }
        };
        push_q(s, 0);
        while(pq.size()) {
            auto [d, i] = pq.top();
            pq.pop();
            // cout << "visit d : " << d << " i : " << i << '\n';
            if(vis[i]) continue;
            // cout << "visit d : " << d << " i : " << i << " dist[i] : " << dist[i] << '\n';
            assert(dist[i] == d);
            vis[i] = 1;
            for(auto [to, w] : adj[i]) {
                push_q(to, d + w);
            }
        }
        for(int i = 0; i < k; i++) cout << dist[i] << " \n"[i == k - 1];
    }

    return 0;
}
