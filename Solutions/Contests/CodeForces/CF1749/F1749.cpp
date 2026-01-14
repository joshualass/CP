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

/*
static fenwick tree impl by chat
*/

const int MAXN = 200001;
const int MAXM = 22;

static ll bit2d[MAXN][MAXM];

void update(int r, int c, ll val) {
    ++r; ++c;
    for (int x = r; x <= MAXN; x += x & -x) {
        for (int y = c; y <= MAXM; y += y & -y) {
            bit2d[x][y] += val;
        }
    }
}

ll query_prefix(int r, int c) {
    // cout << "qp called with r : " << r << " c : " << c << '\n';
    if (r < 0 || c < 0) return 0;
    ++r; ++c;
    ll sum = 0;
    for (int x = r; x > 0; x -= x & -x) {
        for (int y = c; y > 0; y -= y & -y) {
            sum += bit2d[x][y];
        }
    }
    return sum;
}

ll query(int r, int c) {
    return query_prefix(r, c);
}

ll query(int r1, int c1, int r2, int c2) {
    return query_prefix(r2, c2)
         - query_prefix(r2, c1 - 1)
         - query_prefix(r1 - 1, c2)
         + query_prefix(r1 - 1, c1 - 1);
}

//very general HLD template that you can do a lot of fun things with :)
struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> tin, tout, depths, par, heads, starts;
    //heads[i] => for node i, the node with least depth that contains node i in its heavy path
    //starts[i] => where in contiguous memory this point is. 

    HLD(vector<vector<int>> adj) {
        this->adj = adj;
        build();
    }

    void build() {
        this->n = adj.size();
        tin.assign(n, -1);
        tout.assign(n, -1);
        depths.assign(n, -1);
        par.assign(n, -1);

        int time = 0;

        auto euler = [&](auto self, int i, int p, int d) -> void {
            tin[i] = time++;
            depths[i] = d;
            par[i] = p;
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i, d + 1);
                }
            }
            tout[i] = time;
        };

        euler(euler, 0, -1, 0);

        heads.assign(n, -1);
        starts.assign(n, -1);

        time = 0;
        auto hld = [&](auto self, int i, int p, int head) -> void {
            if(head == -1) {
                head = i;
            }

            heads[i] = head;
            starts[i] = time++;

            int hc = -1;
            for(int c : adj[i]) {
                if(c != p) {
                    if(hc == -1 || tout[c] - tin[c] > tout[hc] - tin[hc]) {
                        hc = c;
                    }
                }
            }

            if(hc == -1) return;

            self(self, hc, i, head);
            for(int c : adj[i]) {
                if(c != p && c != hc) {
                    self(self, c, i, -1);
                }
            }
        };

        hld(hld, 0, -1, -1);

        // cout << "tin : " << tin << '\n';
        // cout << "tout : " << tout << '\n';
        // cout << "depths : " << depths << '\n';
        // cout << "par : " << par << '\n';
        // cout << "heads : " << heads << '\n';
        // cout << "starts : " << starts << '\n';

    }

    int lca(int a, int b) {
        while(heads[a] != heads[b]) {
            if(depths[heads[a]] > depths[heads[b]]) {
                a = par[heads[a]];
            } else {
                b = par[heads[b]];
            }
        }
        if(depths[a] < depths[b]) {
            return a;
        } else {
            return b;
        }
    }

    //lca + dist work, see https://cses.fi/problemset/result/15390705/
    int dist(int a, int b) {
        int unc = lca(a, b);
        return depths[b] + depths[a] - depths[unc] * 2;
    }

    vector<array<int,2>> path(int a, int b) {
        vector<array<int,2>> res;

        auto append_path = [&](int cur, int depth) -> void {
            if(depths[cur] < depth) return;
            while(1) {
                if(depths[heads[cur]] <= depth) {
                    res.push_back({starts[heads[cur]] + (depth - depths[heads[cur]]), starts[cur] + 1});
                    break;
                }
                res.push_back({starts[heads[cur]], starts[cur] + 1});
                cur = par[heads[cur]];
            }
        };

        int unc = lca(a, b);
        int unc_depth = depths[unc];

        append_path(a, unc_depth);
        int sz = res.size();
        append_path(b, unc_depth + 1);
        reverse(res.begin() + sz, res.end());
        return res;
    }

    void update(int a, int b, int k, int d) {

        // cout << "update called on a : " << a << " b : " << b << " k : " << k << " d : " << d << '\n';

        vector<array<int,2>> res;

        auto append_path = [&](int cur, int depth) -> void {
            if(depths[cur] < depth) return;
            while(1) {
                if(depths[heads[cur]] <= depth) {
                    int l = starts[heads[cur]] + (depth - depths[heads[cur]]), r = starts[cur] + 1;
                    ::update(l, 20 - d, k);
                    ::update(r, 20 - d, -k);
                    break;
                }
                int l = starts[heads[cur]], r = starts[cur] + 1;
                ::update(l, 20 - d, k);
                ::update(r, 20 - d, -k);
                cur = par[heads[cur]];
            }
        };

        int unc = lca(a, b);
        int unc_depth = depths[unc];

        append_path(a, unc_depth);
        append_path(b, unc_depth + 1);
    }

    // int query(int a, int b, Tree &tree) {
    //     int res = 0;

    //     auto append_path = [&](int cur, int depth) -> void {
    //         if(depths[cur] < depth) return;
    //         while(1) {
    //             if(depths[heads[cur]] <= depth) {
    //                 res = tree.f(res, tree.query(starts[heads[cur]] + (depth - depths[heads[cur]]), starts[cur] + 1));
    //                 break;
    //             }
    //             res = tree.f(res, tree.query(starts[heads[cur]], starts[cur] + 1));
    //             cur = par[heads[cur]];
    //         }
    //     };

    //     int unc = lca(a, b);
    //     int unc_depth = depths[unc];

    //     append_path(a, unc_depth);
    //     append_path(b, unc_depth + 1);
    //     return res;
    // }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HLD hld(adj);

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            int v; cin >> v;
            v--;
            // cout << "start query for i : " << v << '\n';
            ll res = 0;
            for(int i = 20; i >= 0; i--) {
                if(v != -1) {
                    res += query_prefix(hld.starts[v], i);
                    v = hld.par[v];
                }
            }
            cout << res << '\n';

        } else {
            int u, v, k, d; cin >> u >> v >> k >> d;
            u--; v--;
            int unc = hld.lca(u, v);
            hld.update(u, v, k, d);

            if(d) {
                hld.update(u, v, -k, d - 1);
                hld.update(unc, unc, k, d - 1);
            }
            d--;

            while(d >= 0) {
                int nx = hld.par[unc];
                if(nx != -1) {
                    hld.update(nx, nx, k, d);
                    hld.update(unc, unc, -k, d - 1);
                    unc = nx;
                }
                d--;
            }
        }
    }

    return 0;
}
