#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<class T> 
T edmondsKarp(vector<unordered_map<ll, T>>& graph, ll source, ll sink) {
    assert(source != sink);
    T flow = 0;
    vector<ll> par(graph.size());
    vector<ll> q = par;   
    for(;;) {
        fill(par.begin(), par.end(), -1);
        par[source] = 0;
        ll ptr = 1;
        q[0] = source;
        for(ll i = 0; i < ptr; i++){
            ll x = q[i];
            for(auto e : graph[x]) {
                if(par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr ++] = e.first;
                    if(e.first == sink) goto out;
                }
            }
        }
        return flow;
        out: 
        T inc = numeric_limits<T>::max();
        for(ll y = sink; y != source; y = par[y]) {
            inc = min(inc, graph[par[y]][y]);
        }
        flow += inc;
        for(ll y = sink; y != source; y = par[y]) {
            ll p = par[y];
            if((graph[p][y] -= inc) <= 0) {
                graph[p].erase(y);
            }
            graph[y][p] += inc;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    cin >> n >> m;
    vector<array<ll, 3>> e(m);
    ll sum = 0;
    for(ll i = 0; i < m; i++){
        ll u, v, a;
        cin >> u >> v >> a;
        u --, v --;
        e[i] = {u, v, a};
        sum += a;
    }
    ll idptr = 0;
    ll ssource = idptr ++;
    ll ssink = idptr ++;
    vector<ll> nid(n), eid(m);
    for(ll i = 0; i < n; i++) nid[i] = idptr ++;
    for(ll i = 0; i < m; i++) eid[i] = idptr ++;
    ll mxb = 0;
    ll low = 0, high = 1e9;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        vector<unordered_map<ll, ll>> g(idptr);
        for(ll i = 0; i < m; i++) {
            g[ssource][eid[i]] = e[i][2];
            g[eid[i]][nid[e[i][0]]] = e[i][2];
            g[eid[i]][nid[e[i][1]]] = e[i][2];
        }
        for(ll i = 0; i < n; i++) {
            g[nid[i]][ssink] = mid;
        }
        ll flow = edmondsKarp(g, ssource, ssink);
        if(flow == n * mid) {
            mxb = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << sum - (mxb * n) << "\n";

    return 0;
}