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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, m, k; cin >> n >> m >> k;
    string s; cin >> s;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }

    k *= 2;

    vector<vector<char>> states(k + 1, vector<char>(n));
    for(int i = 0; i < n; i++) states[k][i] = s[i];
    for(int turn = k - 1; turn >= 0; turn--) {
        // cout << "turn : " << turn << " good : " << good << " best : " << best << '\n';
        for(int i = 0; i < n; i++) {
            char good = (turn % 2 == 0 ? 'A' : 'B');
            char best = (turn % 2 == 0 ? 'B' : 'A');
            for(int to : adj[i]) {
                if(states[turn + 1][to] == good) {
                    best = good;
                }
            }
            states[turn][i] = best;
        }
    }

    for(int i = 0; i <= k; i++) {
        // cout << "i : " << i << " s[i] : ";
        // for(int j = 0; j < n; j++) cout << states[i][j];
        // cout << '\n';
    }

    cout << (states[0][0] == 'A' ? "Alice" : "Bob") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}