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
const ll inf = ((ll) 1e18) + 1e15;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<ll>> dp(n);
    vector<ll> t;

    auto dfs = [&](auto self, int i, int p) -> void {

        dp[i] = {1, 1};

        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                t.assign(dp[i].size() + dp[c].size() - 1, 0);
                t[0] = 1;
                for(int j = 1; j < dp[i].size(); j++) {
                    for(int k = 0; k < dp[c].size(); k++) {
                        ll add = (inf / dp[i][j] < dp[c][k] ? inf : dp[i][j] * dp[c][k]);
                        t[j + k] = min(inf, t[j + k] + add);
                    }
                }
                dp[i] = t;
            }
        }
    };

    dfs(dfs, 0, -1);

    vector<ll> res(n + 1);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < dp[i].size(); j++) {
            res[j] = min(inf, res[j] + dp[i][j]);
        }
    }

    // for(int i = 1; i <= n; i++) cout << "i ; " << i << " res[i] : " << res[i] << '\n';

    for(int i = 1; i <= n; i++) {
        k -= res[i];
        if(k <= 0) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << "-1\n";

    return 0;
}
