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

//solution - find max sum of degrees among all pairs of nodes that are and are not adjacent to each other. 
//1. for adjacent nodes, we take sum of adjacency list sizes and subtract 2
// we can do this by iterating over all the edges in the graph
//2. for non-adjacent nodes, we take sum of adjacency list sizes and subtract 1. 
// we can do this with tree-dp, returning the largest adjacency list size in each subtree. 

/*
there are some other ways to do this, but this method works without making any observations / guesses
*/

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int res = 0;
    auto dfs = [&](auto self, int i, int p) -> int {
        vector<int> ch;
        for(int c : adj[i]) {
            if(c != p) {
                ch.push_back(self(self, c, i));
                res = max(res, (int) (adj[i].size() + adj[c].size() - 2)); //try adjacent nodes
            }
        }

        //try maximum among all non-adjacent pairs
        sort(ch.begin(), ch.end());
        int par_deg = (p == -1 ? 0 : adj[p].size());

        if(ch.size()) {
            res = max(res, ch.back() + par_deg - 1);
        }
        if(ch.size() >= 2) {
            res = max(res, ch[ch.size() - 1] + ch[ch.size() - 2] - 1);
        }

        //return largest degree in subtree
        int best = adj[i].size();
        if(ch.size()) best = max(best, ch.back());
        return best;
    };

    dfs(dfs, 0, -1);

    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}