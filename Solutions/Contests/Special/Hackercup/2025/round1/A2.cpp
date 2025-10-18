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
    vector<int> a(n);
    for(int &x : a) cin >> x;
    
    int l = 1, r = 1e9;
    while(l != r) {
        int m = (l + r) / 2;
        vector<int> vis(n);
        queue<int> q;
        auto add_q = [&](int x) -> void {
            if(vis[x]) return;
            vis[x] = 1;
            q.push(x);
        };

        for(int i = 0; i < n; i++) {
            if(a[i] <= m) add_q(i);
        }

        while(q.size()) {
            int x = q.front();
            q.pop();
            if(x && abs(a[x - 1] - a[x]) <= m) add_q(x - 1);
            if(x + 1 < n && abs(a[x] - a[x + 1]) <= m) add_q(x + 1);
        }

        if(count(vis.begin(), vis.end(), 1) == n) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << '\n';
    
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    freopen("A2in.txt","r",stdin);
    freopen("A2out.txt","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}