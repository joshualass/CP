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

struct MCMF {
    const ll INF = LLONG_MAX >> 2;

    struct Edge {
        int v;
        ll cap, flow, cost;
    };

    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<pair<int, int>> par;
    vector<int> in_q;
    vector<ll> dist, pi;

    MCMF(int n) : n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}

    void addEdge(int u, int v, ll cap, ll cost) {
        // cout << "adage u : " << u << " v : " << v << " cap : " << cap << " cost : " << cost << '\n';
        int idx = edges.size();
        edges.push_back({v, cap, 0, cost});
        edges.push_back({u, cap, cap, -cost});
        adj[u].push_back(idx);
        adj[v].push_back(idx ^ 1);
    }

    bool find_path(int s, int t) {
        fill(dist.begin(), dist.end(), INF);
        fill(in_q.begin(), in_q.end(), 0);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        in_q[s] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            in_q[cur] = 0;

            for (int idx : adj[cur]) {
                Edge& e = edges[idx];
                int nxt = e.v;
                ll cap = e.cap, fl = e.flow, wt = e.cost;
                ll nxtD = dist[cur] + wt;

                if (fl >= cap || nxtD >= dist[nxt]) continue;

                dist[nxt] = nxtD;
                par[nxt] = {cur, idx};

                if (!in_q[nxt]) {
                    q.push(nxt);
                    in_q[nxt] = 1;
                }
            }
        }
        return dist[t] < INF;
    }

    pair<ll, ll> calc(int s, int t) {
        ll flow = 0, cost = 0;

        while (find_path(s, t)) {
            for (int i = 0; i < n; i++) {
                pi[i] = min(pi[i] + dist[i], INF);
            }

            ll f = INF;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                f = min(f, edges[i].cap - edges[i].flow);
            }

            flow += f;
            for (int v = t, u, i; v != s; v = u) {
                tie(u, i) = par[v];
                edges[i].flow += f;
                edges[i ^ 1].flow -= f;
            }
        }

        for (size_t i = 0; i < edges.size() / 2; i++) {
            cost += edges[i * 2].cost * edges[i * 2].flow;
        }

        return {flow, cost};
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    MCMF mcmf(n + 2);

    int s = n, t = n + 1;
    vector<int> a(n);
    for(int & x: a) cin >> x;
    a.push_back(1e9);
    int f = 0;
    for(int i = 0; i < n; i++) {
        int diff = a[i+1] - a[i];
        if(diff < 0) {  
            f += -diff;
            mcmf.addEdge(s, i, -diff, 0);
        } else if(diff > 0) {
            mcmf.addEdge(i, t, diff, 0);
        }
    }

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        if(l) {
            mcmf.addEdge(l - 1, r, 1e9, 1);
        }
    }

    auto [flow, cost] = mcmf.calc(s, t);

    // cout << "f : " << f << '\n';
    // cout << "flow : " << flow << " cost : " << cost << '\n';

    if(flow != f) {
        cout << "-1\n";
    } else {
        cout << cost << '\n';
    }

    return 0;
}
