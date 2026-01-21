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

//i should definitely try to use dsu more often !

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

ll tri(ll n) {
    return n * (n - 1) / 2;
}

void solve() {
    
    int n; cin >> n;
    dsubuild(n);

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> diffs(n - 1);
    for(int i = 1; i < n; i++) {
        diffs[abs(a[i] - a[i-1]) - 1].push_back(i - 1);
    }

    vector<ll> res(n - 1);
    ll cur = 0;
    for(int i = n - 2; i >= 0; i--) {
        for(int x : diffs[i]) {
            cur -= tri(sizes[find(x)]);
            cur -= tri(sizes[find(x + 1)]);
            merge(x, x + 1);
            cur += tri(sizes[find(x)]);
        }
        res[i] = cur;
    }

    for(int i = 0; i < n - 1; i++) cout << res[i] << " \n"[i == n - 2];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}