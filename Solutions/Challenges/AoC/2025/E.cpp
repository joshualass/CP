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

    vector<array<ll,2>> events;
    ll n; cin >> n;
    for(ll i = 0; i < n; i++) {
        string s; cin >> s;
        ll p = 0;
        for(ll j = 0; j < s.size(); j++) {
            if(s[j] == '-') p = j;
        }
        // cout << "s : " << s << " p : " << p << endl;
        ll lo = stoll(s.substr(0, p)), hi = stoll(s.substr(p + 1));
        // events.push_back({lo, -1});
        // events.push_back({hi, 1});
        events.push_back({lo, 1});
        events.push_back({hi + 1, -1});
    }

    // ll m; cin >> m;
    // for(ll i = 0; i < m; i++) {
    //     string s; cin >> s;
    //     events.push_back({stoll(s), 0});
    // }

    ll res = 0;
    ll cur = 0;
    ll prev = -1;
    sort(events.begin(), events.end());

    // for(auto [time, id] : events) {
    //     if(id == -1) {
    //         cur++;
    //     } else if(id == 0) {
    //         if(cur) res ++;
    //     } else {
    //         cur--;
    //     }
    // }

    for(auto [time, id] : events) {
        if(id == 1) {
            if(cur == 0) {
                prev = time;
            }
            cur++;
        } else {
            cur--;
            if(cur == 0) {
                res += time - prev;
            }
        }
    }

    cout << res << '\n';

    return 0;
}
