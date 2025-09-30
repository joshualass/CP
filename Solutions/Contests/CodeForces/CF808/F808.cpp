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

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};
 
struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;
 
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }
 
    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }
 
    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }
 
    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
 
    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

//need to build sieve, typically with N
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (int i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int n, k; cin >> n >> k;
    
    vector<array<int,3>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    int l = 1, r = 101;
    while(l != r) {
        int m = (l + r) / 2;
        int best_1 = -1;
        vector<int> in(n);
        for(int i = 0; i < n; i++) {
            if(a[i][2] <= m) {
                if(a[i][1] == 1) {
                    if(best_1 == -1 || a[i][0] > a[best_1][0]) {
                        best_1 = i;
                    }
                } else {
                    in[i] = 1;
                }
            }
        }
        if(best_1 != -1) in[best_1] = 1;

        vector<int> id(n, -1);
        int p = 0;
        for(int i = 0; i < n; i++) {
            if(in[i]) id[i] = p++;
        }
        int s = p++;
        int t = p++;
        Dinic d(p, s, t);

        // cout << "m : " << m << " in : " << in << '\n';

        ll res = 0;

        for(int i = 0; i < n; i++) {
            if(in[i]) {
                res += a[i][0];
                if(a[i][1] & 1) {
                    d.add_edge(id[i], t, a[i][0]);
                    // cout << "odd from " << id[i] << " to : " << t << " w : " << a[i][0] << '\n';
                } else {
                    d.add_edge(s, id[i], a[i][0]);
                    // cout << "even from " << s << " to : " << id[i] << " w : " << a[i][0] << '\n';
                    for(int j = 0; j < n; j++) {
                        int sum = a[i][1] + a[j][1];
                        if(in[j] && (a[j][1] & 1) && prime_factor[sum] == sum) {
                            // cout << "prime from " << id[i] << " to : " << id[j] << " w : " << 1e9 << '\n';
                            d.add_edge(id[i], id[j], 1e9);
                        }
                    }
                }
            }
        }

        

        ll flow = d.flow();
        // cout << "res : " << res << " flow : " << flow << '\n';
        res -= flow;

        if(res >= k) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << (l == 101 ? -1 : l) << '\n';

    return 0;
}
