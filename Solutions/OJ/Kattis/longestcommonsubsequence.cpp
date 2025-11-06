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

    int n, k;
    cin >> n >> k;
    vvi adj(k, vi(k, 0));
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < k; j++) {
            for(int _k = j + 1; _k < k; _k++) {
                int u = s[j] - 'A';
                int v = s[_k] - 'A';
                adj[u][v] ++;
                // cout << "UV : " << u << " " << v << " " << i << "\n";
            }
        }
    }
    vvi c(k);
    vi indeg(k, 0);
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            if(adj[i][j] == n) {
                // cout << "EDGE : " << i << " " << j << "\n";
                c[i].push_back(j);
                indeg[j] ++;
            }
        }
    }
    queue<int> q;
    vi dp(k, 0);
    for(int i = 0; i < k; i++) {
        if(indeg[i] == 0) {
            dp[i] = 1;
            q.push(i);
        }
    }
    int ans = 0;
    int vcnt = 0;
    while(q.size() != 0) {
        int cur = q.front();
        q.pop();
        vcnt ++;
        ans = max(ans, dp[cur]);
        for(int x : c[cur]) {
            assert(indeg[x] > 0);
            indeg[x] --;
            dp[x] = max(dp[x], dp[cur] + 1);
            if(indeg[x] == 0) {
                q.push(x);
            }
        }
    }
    assert(vcnt == k);
    cout << ans << "\n";

    return 0;
}
