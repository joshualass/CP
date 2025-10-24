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

//find the last i such that a[i] <= x
int bsearch(vector<ll>& a, ll x) {
    assert(a[0] <= x);
    int low = 0, high = a.size() - 1;
    int ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(a[mid] > x) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
            ans = mid;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, l;
    cin >> n >> m >> l;
    vector<ll> f(n);
    for(int i = 0; i < n; i++) {
        cin >> f[i];
    }
    vector<ll> len(n + 1), off(n + 1);
    ll coff = 0;
    for(int i = 0; i < n; i++) {
        len[i] = l - f[i];
        l -= len[i];
        if(i % 2 == 0) {
            off[i] = coff;
            coff += len[i];
        }
        else {
            coff -= len[i];
            off[i] = coff;
        }
        // cout << "LEN : " << len[i] << "\n";
    }
    len[n] = l;
    if(n % 2 == 0) {
        off[n] = coff;
        coff += len[n];
    }
    else {
        coff -= len[n];
        off[n] = coff;
    }
    vector<ll> bound(m + 1);
    bound[0] = -1e18 - 100;
    for(int i = 1; i <= m; i++) cin >> bound[i];
    vector<ll> ans(m + 1, 0), totinc(m + 1, 0);
    for(int i = 0; i <= n; i++) {
        ll l = off[i], r = off[i] + len[i];
        // cout << "L R : " << l << " " << r << "\n";
        int li = bsearch(bound, l), ri = bsearch(bound, r);
        if(li < ri) {
            ans[li] += bound[li + 1] - l;
            ans[ri] += r - bound[ri];
            li ++;
            totinc[li] ++;
            totinc[ri] --;
        }
        else {
            ans[li] += r - l;
        }
        // cout << "LI RI : " << li << " " << ri << "\n";
    }
    for(int i = 1; i <= m; i++) totinc[i] += totinc[i - 1];
    // for(int i = 0; i <= m; i++) cout << totinc[i] << " ";
    // cout << "\n";
    for(int i = 0; i <= m; i++) {
        if(i == 0 || i == m) {
            assert(totinc[i] == 0);
        }
        else {
            ans[i] += totinc[i] * (bound[i + 1] - bound[i]);
        }
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}
