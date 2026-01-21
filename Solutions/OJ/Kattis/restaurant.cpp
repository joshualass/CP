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

void solve(int n) {
    int l = 0, r = 0;
    for(int i = 0; i < n; i++) {
        string type; cin >> type;
        int x; cin >> x;
        if(type == "DROP") {
            cout << "DROP 2 " << x << '\n';
            r += x;
        } else {
            int take = min(l, x);
            if(take) cout << "TAKE 1 " << take << '\n';
            x -= take;
            l -= take;
            if(x) {
                cout << "MOVE 2->1 " << r << '\n';
                l = r;
                r = 0;
            }
            if(x) {
                cout << "TAKE 1 " << x << '\n';
                l -= x;
            }
        }
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        int n; cin >> n;
        if(n) {
            solve(n);
        } else {
            break;
        }
    }

    return 0;
}