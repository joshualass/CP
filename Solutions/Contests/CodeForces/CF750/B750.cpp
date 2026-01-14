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

    int n; cin >> n;
    int y = 0;
    int ok = 1;
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        string s; cin >> s;

        if(s == "South") {
            y += t;
            if(y > 20000) {
                ok = 0;
            }
        } else if(s == "North") {
            y -= t;
            if(y < 0) {
                ok = 0;
            }
        } else {
            if(y == 0 || y == 20000) {
                // cout << "notok3\n";    
                ok = 0;
            }
        }
    }

    if(y) ok = 0;

    cout << (ok ? "YES" : "NO") << '\n';

    return 0;
}
