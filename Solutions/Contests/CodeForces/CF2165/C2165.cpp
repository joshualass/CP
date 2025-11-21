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

void solve() {
    
    int n, q; cin >> n >> q;
    multiset<int> ms;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ms.insert(x);
    }

    for(int qq = 0; qq < q; qq++) {
        int c; cin >> c;
        int cost = 0;
        multiset<int> inserts, deletes;

        for(int bit = 29; bit >= 0; bit--) {
            if((c >> bit) & 1) {
                // cout << "qq : " << qq << " bit : " << bit << '\n';
                if(ms.lower_bound(1 << (bit + 1)) != ms.end()) break; //there exists a double. we are good. 
                // cout << "did not break\n";
                //check if there exists a number with this already
                if(ms.lower_bound(1 << bit) != ms.end()) {
                    int num = *ms.lower_bound(1 << bit);
                    // cout << "good num num : " << num << '\n';
                    ms.erase(ms.find(num));
                    deletes.insert(num);

                    ms.insert(num ^ (1 << bit));
                    inserts.insert(num ^ (1 << bit));

                } else { //take from the highest. 
                    int mx = *--ms.end();
                    // cout << "near num : " << mx << '\n';
                    cost += (1 << bit) - mx;

                    ms.erase(ms.find(mx));
                    deletes.insert(mx);

                    ms.insert(0);
                    inserts.insert(0);
                }
            }
        }

        cout << cost << '\n';
        for(int x : deletes) {
            ms.insert(x);
        }
        for(int x : inserts) {
            ms.erase(ms.find(x));
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}