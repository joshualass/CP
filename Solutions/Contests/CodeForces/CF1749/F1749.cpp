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

//will need HLD to do this. TODO - WRITE HLD TEMPLATE AND STUFF. 

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

    vector<int> par(n);
    auto dfs = [&](auto self, int i, int p) -> void {
        par[i] = p;
        for(int c : adj[i]) {
            if(c != p) self(self, c, i);
        }
    };

    vector<vector<ll>> deltas(n, vector<ll>(21));

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            int v; cin >> v;
            v--;
            ll res = 0;
            for(int i = 0; i <= 20; i++) {
                if(v != -1) {
                    for(int j = i; j <= 20; j++) {
                        res += deltas[v][j];
                    }
                    v = par[v];
                }
            }
        } else {

        }
    }

    return 0;
}
