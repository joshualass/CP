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

    ll n, m; cin >> n >> m;
    vector<vector<ll>> adj(n);
    for(ll i = 0; i < m; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll sz = a[0];
    a[0] = 0;

    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;

    vector<ll> added_to_queue(n);
    auto add_q = [&](ll i) -> void {
        if(added_to_queue[i]) return;
        added_to_queue[i] = 1;
        pq.push({a[i], i});
    };

    add_q(0);
    while(pq.size()) {
        auto [nx_sz, idx] = pq.top();
        pq.pop();
        if(nx_sz < sz) {
            // cout << "explored idx : " << idx << '\n';
            sz += nx_sz;
            // cout << "current sz after : " << sz << '\n';
            for(ll c : adj[idx]) add_q(c);
        }
    }

    cout << sz << '\n';

    return 0;
}
