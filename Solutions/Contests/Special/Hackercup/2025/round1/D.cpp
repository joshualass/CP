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

/*
struggled a bit on this

it helps a lot to draw it out, maybe write down some observations + Winning and Losing states

else write a program to solve >.<
*/

void solve() {

    int n; cin >> n;
    string s; cin >> s;
    int cur = 0;
    for(char c : s) {
        if(c == 'A') {
            cur++;
        } else {
            cur = max(cur - 1, 0);
        }
    }

    cout << (cur ? "Alice" : "Bob") << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    freopen("Din.txt","r",stdin);
    freopen("Dout.txt","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}