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

    ll n; cin >> n;

    auto ask = [&](ll idx) -> ll {
        cout << idx << endl;
        char dir; cin >> dir;
        if(dir == '>') return 1;
        if(dir == '=') return 0;
        return -1;
    };

    auto search = [&](ll l, ll r) -> ll {
        while(l != r) {
            ll mid = (l + r) / 2;
            ll dir = ask(mid);
            if(dir == -1) {
                r = mid - 1;
            } else if(dir == 0) {
                l = mid;
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    };

    ll x = search(1, n);
    ll y = -1;

    //check to the right
    if(x != n) {
        ll add = 1;
        while(x + add <= n) {
            ll dir = ask(x + add);
            if(dir == 0) {
                y = x + add;
                break;
            } else if(dir == 1) {
                y = search(x + add + 1, min(n, x + add * 2));
                break;
            }
            add = add * 2 + 1;
        }
    }
    if(y == -1) {
        ll sub = 1;
        while(1) {
            ll dir = ask(x - sub);
            if(dir == 0) {
                y = x - sub;
                break;
            } else if(dir == -1) {
                y = search(max(1LL, x - sub * 2 + 1), x - sub - 1);
                break;
            }
            sub *= 2;
        }
    }

    cout << "! " << min(x, y) << " " << max(x, y) << endl;

    return 0;
}
