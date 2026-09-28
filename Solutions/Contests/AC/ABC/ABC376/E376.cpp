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

    int t; cin >> t;
    while(t-->0) {
        int n, k; cin >> n >> k;
        vector<array<int,2>> a(n);
        for(auto &x : a) cin >> x[0];
        for(auto &x : a) cin >> x[1];
        sort(a.begin(), a.end());
    
        ll res = LLONG_MAX;
        ll sum = 0;
        priority_queue<ll> pq;
    
        for(int i = 0; i < k - 1; i++) {
            pq.push(a[i][1]);
            sum += a[i][1];
        }
        for(int i = k - 1; i < n; i++) {
            pq.push(a[i][1]);
            sum += a[i][1];
            if(i != k - 1) {
                sum -= pq.top();
                pq.pop();
            }
            // cout << "i : " << i << " sum : " << sum << " a[i] : " << a[i][0] << '\n';
            res = min(res, a[i][0] * sum);
        }
    
        cout << res << '\n';
    }

    return 0;
}
