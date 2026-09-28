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
    vector<int> a(n), b(n - 1);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    int l = 1, r = 1'000'000'001;
    while(l != r) {
        int m = (l + r) / 2;
        sort(a.begin(), a.end());
        b.push_back(m);
        sort(b.begin(), b.end());
        int ok = 1;
        for(int i = 0; i < n; i++) {
            if(a[i] > b[i]) ok = 0;
        }
        if(ok) {
            r = m;
        } else {
            l = m + 1;
        }
        for(int i = 0; i < n; i++) {
            if(b[i] == m) {
                b.erase(b.begin() + i);
                break;
            }
        }
    }

    cout << (l == 1'000'000'001 ? -1 : l) << '\n';

    return 0;
}
