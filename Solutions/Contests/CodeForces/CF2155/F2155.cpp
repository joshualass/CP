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
struct sparse {
    vector<vector<T>> sparsetable;
    int n, d;
    sparse() {}
    sparse(vector<T> a) {
        buildTable(a);
    }
    T op(T a, T b) {
        return min(a,b);
    }
    void buildTable(vector<T> a) {
        n = a.size();
        d = 32 - __builtin_clz(n);
        sparsetable.assign(n, vector<T>(d));
        for(int depth = 0; depth < d; depth++) {
            for(int i = 0; i < n; i++) {
                if(depth) {
                    sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
                } else {
                    sparsetable[i][depth] = a[i];
                }
            }
        }
    }
    //[l,r) always. 
    T query(int l, int r) {
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }
};

struct LCA {
    int T = 0;
    vector<int> time, path, ret, depth;
    sparse<int> rmq;

    LCA(vector<vector<int>>& C) : time(C.size()), depth(C.size()), rmq((dfs(C, 0, -1, 0), ret)) {}

    void dfs(vector<vector<int>>& C, int v, int par, int d) {
        time[v] = T++;
        depth[v] = d;
        for (int y : C[v]) if (y != par) {
            path.push_back(v);
            ret.push_back(time[v]);
            dfs(C, y, v, d + 1);
        }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        int ta = time[a], tb = time[b];
        if (ta > tb) swap(ta, tb);
        return path[rmq.query(ta, tb)];
    }
    int dist(int a,int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

const int MAXN = 300000;
vector<int> ch[MAXN]; //colors here, stores vector of the colors at this node. 
int in[MAXN], out[MAXN], attime[MAXN], bid[MAXN * 2], nc[MAXN], cc[MAXN], vc[MAXN + 1], res[MAXN];
vector<vector<int>> adj;

void dfs(int i, int p, int &time) {
    attime[time] = i;
    in[i] = time++;
    for(int c : adj[i]) {
        if(c != p) {
            dfs(c, i, time);
        }
    }
    attime[time] = i;
    out[i] = time++;
}

void solve() {
    
    int n, k, s, q; cin >> n >> k >> s >> q;
    adj.clear();
    adj.resize(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++) ch[i].clear();

    for(int i = 0; i < s; i++) {
        int v, x; cin >> v >> x;
        v--; x--;
        ch[v].push_back(x);
    }

    LCA lca(adj);
    int time = 0;
    dfs(0, -1, time);

    int SQ = sqrt(n + s);
    
    int cb = -1, sz = 1e9;
    for(int i = 0; i < n * 2; i++) {
        int node = attime[i];
        int add = 1 + ch[node].size();
        if(sz + add > SQ) {
            cb++;
            sz = node + add;
        }
        bid[i] = cb;
    }

    vector<array<int,6>> queries(q);

    for(int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        if(in[u] > in[v]) swap(u, v);
        int anc = lca.lca(u, v);
        if(anc == u || anc == v) {
            queries[i] = {in[u], in[v], bid[in[u]], bid[in[v]], -1, i};
        } else {
            if(ch[anc].size() >= SQ) {
                queries[i] = {out[u], in[v], bid[out[u]], bid[in[v]], anc, i};
            } else {
                queries[i] = {out[u], in[v], bid[out[u]], bid[in[v]], -1, i};
            }
        }
    }

    sort(queries.begin(), queries.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        if(lhs[4] == rhs[4]) {
            if(lhs[2] == rhs[2]) {
                if(lhs[2] % 2 == 0) {
                    return lhs[3] < rhs[3];
                } else {
                    return lhs[3] > rhs[3];
                }
            } else {
                return lhs[2] < rhs[2];
            }
        } else {
            return lhs[4] < rhs[4];
        }
    });

    fill(nc, nc + n, 0);
    fill(cc, cc + k, 0);
    fill(vc, vc + n + 1, 0);
    vc[0] = k;

    int cl = 0, cr = -1;

    auto toggle = [&](int idx) -> void {
        int node = attime[idx];
        for(int color : ch[node]) {
            vc[cc[color]]--;
            if(nc[node] == 0) {
                cc[color]++;
            } else {
                cc[color]--;
            }
            vc[cc[color]]++;
        }
        nc[node] ^= 1;
    };

    int ex = -1;

    // cout << "in\n";
    // for(int i = 0; i < n; i++) cout << in[i] << " \n"[i == n - 1];
    // cout << "out\n";
    // for(int i = 0; i < n; i++) cout << out[i] << " \n"[i == n - 1];

    // cout << "attime\n";
    // for(int i = 0; i < n * 2; i++) cout << attime[i] << " \n"[i == n * 2 - 1];

    for(auto [l, r, lbid, rbid, imp_anc, id] : queries) {

        // cout << "l : " << l << " r : " << r << " lbid  " << lbid << " rbid : " << rbid << " anc : " << imp_anc << " id : " << id << '\n';
        int path_length = lca.dist(attime[l], attime[r]) + 1;
        // cout << "pl : " << path_length << '\n';

        while(cl > l) toggle(--cl);
        while(cr < r) toggle(++cr);
        while(cl < l) toggle(cl++);
        while(cr > r) toggle(cr--);

        //erase previous important anc
        if(ex != -1 && ex != imp_anc) {
            toggle(ex);
            ex = -1;
        }
        //ex will be -1 except for the case where anc is the same as previous. 

        int anc = lca.lca(attime[l], attime[r]);
        // cout << "anc : " << anc << '\n';

        if(anc == attime[l] || anc == attime[r]) {
            //no more toggles are needed
            res[id] = vc[path_length];
            // cout << "nc states1\n";
            // for(int i = 0; i < n; i++) cout << nc[i] << " \n"[i == n - 1];
        } else {
            if(ex != anc) {
                ex = anc;
                toggle(anc);
            }
            // cout << "nc states2\n";
            // for(int i = 0; i < n; i++) cout << nc[i] << " \n"[i == n - 1];
            res[id] = vc[path_length];
        }
        // cout << "ex : " << ex << '\n';
        // cout << "res val : " << res[id] << '\n';
    }

    for(int i = 0; i < q; i++) cout << res[i] << " \n"[i == q - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}