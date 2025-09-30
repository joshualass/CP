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

    int n, m; cin >> n >> m;
    vector<vector<array<int,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back({v, 0});
        adj[v].push_back({u, 1});
    }

    vector<int> dist(n, -1);
    int d = 0;
    queue<int> q1;

    q1.push(0);

    while(q1.size()) {
        queue<int> nx;
        while(q1.size()) {
            int x = q1.front();
            q1.pop();
            nx.push(x);
            for(auto [to, w] : adj[x]) {
                if(w == 0 && dist[to] == -1) {
                    dist[to] = d;
                    q1.push(to);
                }
            }
        }
        d++;
        while(nx.size()) {
            int x = nx.front();
            nx.pop();
            for(auto [to, w] : adj[x]) {
                if(dist[to] == -1) {
                    dist[to] = d;
                    q1.push(to);
                }
            }
        }
    }

    cout << dist[n - 1] << '\n';
    

    return 0;
}
