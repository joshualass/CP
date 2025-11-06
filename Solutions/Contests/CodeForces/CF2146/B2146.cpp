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
    
    int n, m; cin >> n >> m;
    vector<int> cnts(m);
    vector<vector<int>> s(n);
    for(int i = 0; i < n; i++) {
        int l; cin >> l;
        for(int j = 0; j < l; j++) {
            int x; cin >> x;
            x--;
            cnts[x]++;
            s[i].push_back(x);
        }
    }

    if(count(cnts.begin(), cnts.end(), 0)) {
        cout << "NO\n";
        return;
    }

    vector<int> g;

    for(int i = 0; i < n; i++) {
        int ok = 1;
        for(int x : s[i]) {
            if(cnts[x] == 1) ok = 0;
        }
        if(ok) g.push_back(i);
    }

    cout << (g.size() <= 1 ? "NO" : "YES") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}