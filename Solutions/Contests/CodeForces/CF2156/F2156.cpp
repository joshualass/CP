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

int debug = 1;
int n;
vector<int> a, res;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    

}

void solve_slow() {

    set<vector<int>> vis;
    queue<vector<int>> q;

    auto add_q = [&](vector<int> b) -> void {
        if(vis.count(b)) return;
        vis.insert(b);
        q.push(b);
    };

    add_q(a);
    while(q.size()) {
        vector<int> b = q.front();
        q.pop();
        vector<int> ridx(n);
        for(int i = 0; i < n; i++) {
            ridx[b[i]] = i;
        }
        for(int i = 0; i < n; i++) {
            if(b[i] >= 2 && ridx[b[i] - 1] > i && ridx[b[i] - 2] > i) {
                vector<int> nx = b;
                int j = ridx[b[i] - 1], k = ridx[b[i] - 2];
                nx[i] -= 2;
                nx[j]++;
                nx[k]++;
                add_q(nx);
            }
        }
    }

    res = *vis.begin();

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug) {
        cin >> n;
        a.assign(n, 0);
        for(int &x : a) {
            cin >> x;
            x--;
        }
        solve_slow();
        cout << "a : " << a << '\n';
        cout << "res : " << res << '\n';
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}