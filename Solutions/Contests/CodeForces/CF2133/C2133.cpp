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
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> dists(n);

    auto ask = [&](int x, vector<int> s) -> int {
        cout << "? " << x + 1 << " " << s.size();
        for(int x : s) cout << " " << x + 1;
        cout << endl;
        int res; cin >> res;
        return res;
    };

    for(int i = 0; i < n; i++) {
        vector<int> a(n);
        iota(a.begin(), a.end(), 0);
        dists[i] = ask(i, a);
    }

    int mx = 0;
    for(int i = 1; i < n; i++) {
        if(dists[i] > dists[mx]) mx = i;
    }

    vector<int> path;
    while(dists[mx] > 1) {
        path.push_back(mx);
        int cand = -1;
        for(int i = 0; i < n; i++) {
            if(dists[i] == dists[mx] - 1) {
                vector<int> q;
                for(int j = 0; j < n; j++) {
                    if(j == i || j == mx || dists[j] < dists[mx] - 1) {
                        q.push_back(j);
                    }
                }
                int res = ask(mx, q);
                if(res == dists[mx]) {
                    cand = i;
                }
            }
        }
        mx = cand;
    }

    path.push_back(mx);

    cout << "! " << path.size();
    for(int x : path) cout << " " << x + 1;
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}