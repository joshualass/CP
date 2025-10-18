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
const int SQN = 200;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    set<int> s(a.begin(), a.end());
    map<int,int> cm;
    int p = 0;
    for(int x : s) cm[x] = p++;
    for(int &x : a) x = cm[x];

    vector<int> in(n), out(n);
    vector<int> attime;
    int time = 0;
    auto dfs = [&](auto self, int i, int p) -> void {
        in[i] = time++;
        attime.push_back(i);
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
        out[i] = time++;
        attime.push_back(i);
    };

    dfs(dfs, 0, -1);

    //atbucket[i] stores the bucket each index is in
    vector<int> atbucket;
    int cur_bucket = 0, sz = 0;

    for(int i = 0; i < attime.size(); i++) {
        if(sz + 1 > SQN) {
            cur_bucket++;
            sz = 1;
        }
        atbucket.push_back(cur_bucket);
    }

    int bc = cur_bucket + 1;

    //[l][r] => vector of tuples of the form {true l, true r, query id}
    vector<vector<vector<array<int,3>>>> queries(bc, vector<vector<array<int,3>>>(bc));
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        //ensure we visit node l first
        if(in[l] > in[r]) swap(l, r);
        int lidx = in[l], ridx = out[r] - 1;
        int lb = atbucket[lidx], rb = atbucket[ridx];
        queries[lb][rb].push_back({lidx, ridx, i});
    }

    vector<int> cnts_value(p), cnts_node(n);
    int cur = 0;

    auto toggle = [&](int idx) -> void {
        int node = attime[idx];
        int val = a[node];

        cur -= cnts_value[val] > 0;
        if(cnts_node[node] == 0) {
            cnts_value[val]++;
        } else {
            cnts_value[val]--;
        }
        cnts_node[node] ^= 1;

        cur += cnts_value[val] > 0;
    };


    vector<int> res(m);
    int curl = 0, curr = -1;

    auto handle_queries = [&](int i, int j) -> void {
        for(auto [l, r, id] : queries[i][j]) {
            while(curl > l) {
                toggle(--curl);
            }
            while(curr < r) {
                toggle(++curr);
            }
            while(curl < l) {
                toggle(curl++);
            }
            while(curr > r) {
                toggle(curr--);
            }
            res[id] = curr;
        }
    };


    for(int i = 0; i < bc; i++) {
        if(i % 2 == 0) {
            for(int j = i; j < bc; j++) {
                handle_queries(i, j);
            }
        } else {
            for(int j = bc - 1; j >= i; j--) {
                handle_queries(i, j);
            }
        }
    }

    for(int i = 0; i < m; i++) cout << res[i] << "\n";

    return 0;
}
