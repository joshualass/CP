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
    vector<string> a(n);
    int res = 0;
    for(auto &x : a) {
        cin >> x;
        res += count(x.begin(), x.end(), '1');
    }
    int mx = 0;
    
    vector<int> dx = {1,-1,0,0, 1, 1, -1, -1}, dy = {0,0,1,-1, 1, -1, 1, -1};
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '0') {
                mx = max(mx, 1);
                for(int k = 0; k < 8; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if(ni >= 0 && ni < n && nj >= 0 && nj < m && a[ni][nj] == '0') {
                        mx = max(mx, 2);
                    }
                }
            }
        }
    }

    cout << res - (2 - mx) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}