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

    int sz = 0, l = 0;
    vector<array<int,2>> buckets;
    vector<int> atbucket;

    for(int i = 0; i < attime.size(); i++) {
        if(sz + 1 > SQN) {
            buckets.push_back({l, i - 1});
            l = i;
            sz = 1;
        }
        atbucket.push_back(buckets.size());
    }

    buckets.push_back({l, n - 1});

    vector<vector<array<int,3>>> queries(buckets.size(), vector<array<int,3>>(buckets.size()));
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        //push to start times, 
    }

    return 0;
}
