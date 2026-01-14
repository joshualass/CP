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

    int n, m, k, q; cin >> n >> m >> k >> q;
    vector<set<array<int,2>>> adj(n);
    vector<map<int,int>> cnts(k);

    for(int i = 0; i < m; i++) {
        int u, v, k; cin >> u >> v >> k;
        u--; v--; k--;
        adj[u].insert({v, k});
    }

    vector<int> vis(n);
    int cnt = 0;

    auto visit = [&](int idx) -> void {
        if(vis[idx]) return;
        vis[idx] = 1;
        cnt++;

        for(auto [v, k] : adj[idx]) {
            cnts[k][v]++;
        }
    };

    visit(0);

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int u, v, k; cin >> u >> v >> k;
            u--; v--; k--;
            adj[u].insert({v, k});
            if(vis[u]) cnts[k][v]++;
        } else if(type == 2) {
            int u, v, k; cin >> u >> v >> k;
            u--; v--; k--;
            if(vis[u]) cnts[k][v]--;
            adj[u].erase({v, k});
        } else if(type == 3) {
            int k; cin >> k;
            k--;
            vector<int> visit_list;
            for(auto [idx, cnt] : cnts[k]) {
                if(cnt > 0) visit_list.push_back(idx);
            }
            cnts[k].clear();
            for(int x : visit_list) visit(x);
            cout << cnt << '\n';
        }
    }

    return 0;
}
