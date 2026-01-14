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
1
6 4

*/

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a;
    if(k & 1) {
        for(int i = 0; i < k; i++) a.push_back(n);
    } else {
        // int x = n, y = 0;
        // for(int bit = 30; bit >= 0; bit--) {
        //     if((x >> bit) & 1) {
        //         x -= 1 << bit;
        //         y += 1 << bit;
        //         break;
        //     }
        // }

        // int start = 0;

        // // cout << "x : " << x << " y : " << y << '\n';

        // for(int bit = 30; bit >= 0; bit--) {
        //     if((x >> bit) & 1) {
        //         // cout << "start : " << bit << '\n';
        //         start = 1;
        //     } else if(start) {
        //         // cout << "mih bit : " << bit << '\n';
        //         x += 1 << bit;
        //         y += 1 << bit;
        //     }

        // }

        // a.push_back(x);
        // a.push_back(y);
        // for(int i = 2; i < k; i++) a.push_back(n);

        int rem = n;

        for(int i = 0; i < k; i += 2) {
            int f = -1, s = -1;
            for(int bit = 30; bit >= 0; bit--) {
                if((rem >> bit) & 1) {
                    rem ^= 1 << bit;
                    f = bit;
                    break;
                }
            }
            for(int bit = 30; bit >= 0; bit--) {
                if((rem >> bit) & 1) {
                    rem ^= 1 << bit;
                    s = bit;
                    break;
                }
            }

            // cout << "i : " << i << " f : " << f << " s : " << s << '\n';
            int x = n, y = n;
            if(f != -1) x ^= 1 << f;
            if(s != -1) y ^= 1 << s;
            for(int bit = min(f,s)-1; bit >= 0; bit--) {
                x |= 1 << bit;
                y |= 1 << bit;
            }
            a.push_back(x);
            a.push_back(y);
        }

        a[0] ^= rem;
        
    }

    for(int x : a) cout << x << " ";
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}