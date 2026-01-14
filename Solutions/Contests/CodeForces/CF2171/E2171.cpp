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
    
    int n; cin >> n;
    vector<int> res(n, -1);
    set<int> unvis;
    for(int i = 1; i <= n; i++) unvis.insert(i);

    int cur = 2;
    for(int i = 0; i < n; i++) {
        if(i % 3 == 0) continue;
        if(cur % 2 == 0) {
            if(cur > n) {
                cur = 3;
            } else {
                res[i] = cur;
                unvis.erase(cur);
                cur += 2;
            }
        }
        if(cur % 2 == 1) {
            if(cur > n) break;
            res[i] = cur;
            unvis.erase(cur);
            cur += 6;
        }
    }   

    for(int i = 0; i < n; i++) {
        if(res[i] == -1) {
            res[i] = *unvis.begin();
            unvis.erase(unvis.begin());
        }
    }

    for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}