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
    
    int n; cin >> n;
    string s; cin >> s;
    int ok = 1;
    int prev_idx = -1, bm = 1;
    for(int i = 0; i < n; i++) {

        if(s[i] == '0') {
            int nx = 0;
            //case previous rabbit is directly before
            if(prev_idx + 1 == i) {
                nx = 3;
            } else if(prev_idx + 2 == i) { //case 2 before, we have to do the opposite that is allowed. 
                if(bm & 1) nx |= 2;
                if(bm & 2) nx |= 1;
            } else {
                if(bm == 2) ok = 0;
                nx = 2;
            }
            bm = nx;
            prev_idx = i;
        }
    }
    if(bm == 2 && s.back() != '0') ok = 0;
    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}