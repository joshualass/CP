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
    vector<int> res(n * 2, -1);
    vector<int> g1, g2;
    g1.push_back(0);

    auto ask = [&](vector<int> a) -> int {
        cout << "? " << a.size();
        for(int x : a) cout << " " << x + 1;
        cout << endl;
        int res; cin >> res;
        res--;
        return res;
    };

    for(int i = 1; i < n * 2; i++) {
        vector<int> query = g1;
        query.push_back(i);
        int mad = ask(query);
        if(mad == -1) {
            g1.push_back(i);
        } else {
            g2.push_back(i);
            res[i] = mad;
        }
    }

    for(int x: g1) {
        vector<int> query = g2;
        query.push_back(x);
        int mad = ask(query);
        res[x] = mad;l
    }

    cout << "!";
    for(int x : res) cout << " " << x + 1;
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}