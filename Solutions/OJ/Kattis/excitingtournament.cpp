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
#include <bits/extc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct edge {
        int from, to, rev;
        ll cap, cost, flow;
    };
    int N;
    vector<vector<edge>> ed;
    vi seen;
    vector<ll> dist, pi;
    vector<edge*> par;
    
    MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}
    
    void addEdge(int from, int to, ll cap, ll cost) {
        if (from == to) return;
        ed[from].push_back(edge{from, to, sz(ed[to]), cap, cost, 0});
        ed[to].push_back(edge{to, from, sz(ed[from])- 1, 0, -cost, 0});
    }
    
    void path(int s) {
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0; ll di;
        
        __gnu_pbds::priority_queue<pair<ll,int>> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({0, s});
        
        while(!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for(edge & e : ed[s]) if(!seen[e.to]) {
                ll val = di - pi[e.to] + e.cost;
                if(e.cap - e.flow > 0 && val < dist[e.to]) {
                    dist[e.to] = val;
                    par[e.to] = &e;
                    if(its[e.to] == q.end()) {
                        its[e.to] = q.push({ -dist[e.to], e.to });
                    } else {
                        q.modify(its[e.to], { -dist[e.to], e.to });
                    }
                }
            }
        }
        rep(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
    }
    
    pair<ll,ll> maxflow(int s, int t) {
        ll totflow = 0, totcost = 0;
        while(path(s), seen[t]) {
            ll fl = INF;
            for(edge* x = par[t]; x; x = par[x->from]) {
                fl = min(fl, x->cap - x->flow);
            }
            
            totflow += fl;
            for(edge* x = par[t]; x ; x = par[x->from]) {
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        rep(i, 0, N) for(edge & e : ed[i]) totcost += e.cost * e.flow;
        return {totflow, totcost / 2};
    }
    
    void setpi(int s) {
        fill(all(pi), INF); pi[s] = 0;
        int it = N, ch = 1; ll v;
        while(ch-- && it--) {
            rep(i, 0, N) if(pi[i] != INF) 
                for(edge & e : ed[i]) if(e.cap) 
                    if((v = pi[i] + e.cost) < pi[e.to])
                        pi[e.to] = v, ch = 1;
        }
        assert(it >= 0);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    
    int best = 0;
    for(int i = 1; i < n; i++) {
        if(a[i][0] > a[best][0]) best = i;
    }
    
    {
        MCMF mcmf(n * 2 + 2);
        int s = n * 2, t = n * 2 + 1;
        for(int i = 0; i < n; i++) {
            
            for(int j = 0; j < n; j++) {
                if(a[i][0] > a[j][0]) {
                    mcmf.addEdge(i, j + n, 1, a[i][0] ^ a[j][0]);
                }
            }
            
            if(i == best) {
                mcmf.addEdge(s, i, a[i][1], 0);
            } else {
                mcmf.addEdge(i + n, t, 1, 0);
                mcmf.addEdge(s, i, a[i][1] - 1, 0);
            }
        }
        
        auto [flow, cost] = mcmf.maxflow(s, t);
        
        // cout << "flow : " << flow << " cost : " << cost << '\n';
        
        cout << cost << " ";
    }
    
    {
        MCMF mcmf(n * 2 + 2);
        int s = n * 2, t = n * 2 + 1;
        for(int i = 0; i < n; i++) {
            
            for(int j = 0; j < n; j++) {
                if(a[i][0] > a[j][0]) {
                    mcmf.addEdge(i, j + n, 1, - (a[i][0] ^ a[j][0]));
                }
            }
            
            if(i == best) {
                mcmf.addEdge(s, i, a[i][1], 0);
            } else {
                mcmf.addEdge(i + n, t, 1, 0);
                mcmf.addEdge(s, i, a[i][1] - 1, 0);
            }
        }
        
        mcmf.setpi(s);
        auto [flow, cost] = mcmf.maxflow(s, t);
        
        // cout << "flow : " << flow << " cost : " << cost << '\n';
        
        cout << -cost << "\n";
    }

    return 0;
}
