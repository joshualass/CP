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
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> in(n);
    for(int i = 1; i < n; i++) {
        int u, v, x, y; cin >> u >> v >> x >> y;
        u--; v--;
        if(x > y) swap(u, v);
        adj[u].push_back(v);
        in[v]++;
    }

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(in[i] == 0) q.push(i);
    }
    vector<int> res(n);
    int p = 0;
    while(q.size()) {
        int x = q.front();
        q.pop();
        res[x] = ++p;
        for(int to : adj[x]) {
            in[to]--;
            if(in[to] == 0) q.push(to);
        }
    }

    for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}