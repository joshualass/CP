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
typedef vector<int> vi;
typedef vector<vi> vvi;


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vvi adj(n, vi(n, 0));
    for(int i = 0; i < m; i++) {
        string s;
        cin >> s;
        int amt;
        cin >> amt;
        for(int j = 0; j < n; j++) {
            for(int k = j + 1; k < n; k++) {
                int u = s[j] - 'A';
                int v = s[k] - 'A';
                adj[u][v] += amt;
                adj[v][u] -= amt;
            }
        }
    }
    set<int> g;
    for(int i = 0; i < n; i++) {
        bool ing = true;
        for(int j = 0; j < n; j++) {
            if(adj[i][j] < 0) ing = false;
        }
        if(ing) g.insert(i);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) cout << adj[i][j] << " ";
        cout << "\n";
    }
    if(g.size() >= 3) {
        cout << g.size() << "\n";
        return 0;
    }
    // cout << "G : ";
    // for(auto i = g.begin(); i != g.end(); i++) cout << *i << " ";
    // cout << "\n";
    int ans = 1e9;
    for(int a = 0; a < n; a++) {
        for(int b = 0; b < n; b++) {
            for(int c = 0; c < n; c++) {
                if(a == b || b == c || a == c) continue;
                set<int> s;
                s.insert(a);
                s.insert(b);
                s.insert(c);
                bool sub = true;
                for(auto i = g.begin(); i != g.end(); i++) {
                    if(!s.count(*i)) sub = false;
                }
                if(!sub) continue;
                int x = adj[a][b];
                int y = adj[b][c];
                int z = adj[c][a];
                // cout << "XYZ : " << x << " " << y << " " << z << " " << a << " " << b << " " << c << "\n";
                if(x < y) swap(x, y);
                if(x < z) swap(x, z);
                if(y < z) swap(y, z);
                assert(x >= y && y >= z);
                int cans = 1e9;
                if(z >= 1) cans = 0;
                else if(y >= 1) cans = max(0, 1 - z);
                else if(x >= 1) {
                    cans = max(0, 1 - y) + max(0, 1 - z);
                    int extra = x - 1;
                    int both = min(1 - y, 1 - z);
                    cans -= min(extra, both);
                }
                else cans = max(0, 1 - x) + max(0, 1 - y) + max(0, 1 - z);
                ans = min(ans, cans);
            }
        }
    }
    cout << ans << "\n";

    return 0;
}
