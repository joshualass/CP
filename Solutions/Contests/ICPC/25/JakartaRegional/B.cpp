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

bool is_valid(int n, vector<int>& a, int val) {
    vector<int> pfx(n + 1, 0);
    for(int i = 0; i < n; i++) {
        if(a[i] >= val) continue;
        int diff = val - a[i] - 1;
        int l = i - diff, r = i + diff + 1;
        l = max(0, l), r = min(n, r);
        pfx[l] ++, pfx[r] --;
    }
    //left edge
    pfx[0] ++, pfx[val - 1] --;
    //right edge
    pfx[n - val + 1] ++, pfx[n] --;
    for(int i = 1; i <= n; i++) pfx[i] += pfx[i - 1];
    for(int i = 0; i < n; i++) if(pfx[i] == 0) return true;
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int low = 1, high = n, ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(n, a, mid)) {
            ans = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";

    return 0;
}
