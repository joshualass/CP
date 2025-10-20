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

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int sum = accumulate(a.begin(), a.end(), 0);

    for(int qq = 0; qq < q; qq++) {
        int t; cin >> t;
        t = sum - t;
        // cout << "t : " << t << endl;
        int l = 0, r = -1;
        int f = 0, cur = 0;
        if(t == 0) {
            f = 1;
        } else {
            if(t > 0) {
                while(1) {
                    if(cur < t) {
                        if(r == n - 1) break;
                        r++;
                        cur += a[r];
                    } else {
                        cur -= a[l];
                        l++;
                    }
                    if(cur == t) f = 1;
                }
            }
        }
        cout << (f ? "Yes" : "No") << '\n';
    }

    return 0;
}
