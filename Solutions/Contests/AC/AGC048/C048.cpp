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

/*
stop guessing. 

There is no advantage of moving a slider away from a correct position.
Then, we need to see how many sliders we need to help that and 

it could almost be dsu like when we move a slider over. 
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l; cin >> n >> l;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    int ok = 1;
    ll res = 0;

    auto solve = [&]() -> void {

        map<int,vector<int>> m;
        for(int i = 0; i < n; i++) {
            m[a[i] - i].push_back(i);
        }
        m[l + 1 - n].push_back(n);

        set<int> vis;
        for(int i = 0; i < n; i++) {
            int cur = a[i], targ = b[i];
            // cout << "i : " << i << " cur : " << cur << " targ : " << targ << '\n';
            if(targ > cur) {
                int goal = b[i] - i;
                if(m.count(goal)) {
                    if(vis.count(goal)) continue;
                    int last = m[goal].back();
                    int move = last - i - m[goal].size() + 1;
                    // cout << "add move : " << move << '\n';
                    res += move;
                    vis.insert(goal);
                } else {
                    // cout << "missed!\n";
                    ok = 0;
                }
            }
        }

    };

    solve();

    for(int i = 0; i < n; i++) {
        a[i] = l - a[i] + 1;
        b[i] = l - b[i] + 1;
    }

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    solve();

    cout << (ok ? res : -1) << '\n';

    return 0;
}
