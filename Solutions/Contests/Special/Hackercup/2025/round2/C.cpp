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

    int n, k, m; cin >> n >> k >> m;
    vector<map<int,int>> unvis_routes(m); //unvisited routes in order, {time, node}
    vector<map<int,int>> route_pos(m); //find which index a node is in a route
    vector<vector<int>> routes_contain(n); //which routes contain this node
    vector<int> res(n, -1); //which nodes have been visited

    for(int i = 0; i < m; i++) {
        int l; cin >> l;
        int time = 0;
        for(int j = 0; j < l; j++) {
            int x; cin >> x;
            x--;
            unvis_routes[i][time] = x;
            route_pos[i][x] = time;
            routes_contain[x].push_back(i);
            time++;
        }
    }

    int dist = 0;
    vector<int> q;

    auto add_q = [&](int i) -> void {
        if(res[i] != -1) return;
        res[i] = dist;
        q.push_back(i);
        for(int r : routes_contain[i]) {
            unvis_routes[r].erase(route_pos[r][i]);
        }
    };

    add_q(0);

    while(q.size()) {
        dist++;
        vector<int> to_vis;
        swap(q, to_vis);
        for(int x : to_vis) {
            for(int r : routes_contain[x]) {
                while(1) {
                    int start_time = route_pos[r][x];
                    auto next = unvis_routes[r].upper_bound(start_time);
                    if(next == unvis_routes[r].end()) break;
                    auto [time, node] = *next;
                    if(time - start_time <= k) {
                        add_q(node);
                    } else {
                        break;
                    }
                }
            }
        }
    }

    ll sum = 0;
    for(int i = 0; i < n; i++) sum += 1LL * (i + 1) * res[i];
    cout << sum << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    freopen("Cin.txt","r",stdin);
    freopen("Cout.txt","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}