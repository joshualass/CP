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

    ll n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> a(n, vector<ll>(m));
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<vector<int>> vis(n, vector<int>(m));
    vector<ll> best;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == -1) break;
            if(vis[i][j] == 0) {
                best.push_back(a[i][j]);
                vis[i][j] = 1;
            }
        }
    }

    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            if(a[i][j] == -1) break;
            if(vis[i][j] == 0) {
                best.push_back(a[i][j]);
                vis[i][j] = 1;
            }
        }
    }    

    sort(best.rbegin(), best.rend());
    ll res = 0;
    for(int i = 0; i < min(k, (ll) best.size()); i++) res += best[i];
    cout << res << '\n';

    return 0;
}
