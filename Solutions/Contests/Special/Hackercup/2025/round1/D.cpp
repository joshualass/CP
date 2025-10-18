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
    char p = 'A';
    vector<pair<char,int>> a;
    a.push_back({'A', 0});
    for(char c : s) {
        if(c != p) {
            a.push_back({c, 0});
        }
        a.back().second++;
        p = c;
    }
    if(a.back().first != 'B') a.push_back({'B', 0});

    int f = 0;
    assert(a.size() % 2 == 0);
    for(int i = 0; i < a.size(); i += 2) {
        if(a[i].second > a[i + 1].second) f = 1;
    }

    cout << (f ? "Alice" : "Bob") << '\n';
    
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