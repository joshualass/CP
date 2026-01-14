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

void solve_first() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dists(n, -1);
    queue<array<int,2>> q;
    q.push({0,0});

    while(q.size()) {
        auto [node, dist] = q.front();
        q.pop();
        if(dists[node] != -1) continue;
        dists[node] = dist;
        for(int x : adj[node]) q.push({x, dist + 1});
    }

    for(int i = 0; i < n; i++) {
        if(dists[i] % 3 == 0) {
            cout << 'r';
        } else if(dists[i] % 3 == 1) {
            cout << 'b';
        } else {
            cout << 'g';
        }
    }

    cout << '\n';

}

void solve_second() {
    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int n; cin >> n;
        string s; cin >> s;
        if(count(s.begin(), s.end(), 'r') == n || count(s.begin(), s.end(), 'b') == n || count(s.begin(), s.end(), 'g') == n) {
            cout << "1\n";
        } else if(count(s.begin(), s.end(), 'r') == 0) {
            for(int i = 0; i < n; i++) {
                if(s[i] == 'g') {
                    cout << i + 1 << '\n';
                    break;
                }
            }
        } else if(count(s.begin(), s.end(), 'b') == 0) {
            for(int i = 0; i < n; i++) {
                if(s[i] == 'r') {
                    cout << i + 1 << '\n';
                    break;
                }
            }
        } else if(count(s.begin(), s.end(), 'g') == 0) {
            for(int i = 0; i < n; i++) {
                if(s[i] == 'b') {
                    cout << i + 1 << '\n';
                    break;
                }
            }
        }

    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string type; cin >> type;

    int casi; cin >> casi;
    while(casi-->0) {
        if(type == "first") solve_first();
        if(type == "second") solve_second();
    }

    return 0;
}