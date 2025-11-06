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
typedef vector<int> vi;
typedef vector<ll> vl;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    cin >> n >> c;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int S = 0;
    for(int i = 0; i < n; i++) S += a[i];
    set<int> s;
    s.insert(0);
    vector<bool> dp(c + 1, 0);
    int ans = c;
    dp[0] = 1;
    int aptr = 0;
    for(int x = c; x >= 0; x--) {
        while(aptr != n && a[aptr] > x) {
            int val = a[aptr ++];
            S -= val;
            for(int i = c; i >= 0; i--) {
                if(i + val > c) continue;
                if(!dp[i]) continue;
                if(!dp[i + val]) {
                    s.insert(i + val);
                    dp[i + val] = 1;
                }
            }
        }
        // cout << "S : " << x << " " << S << "\n";
        if(S > c) continue;
        int req = (c - x) - S;
        // cout << "REQ : " << x << " " << req << "\n";
        auto sptr = s.lower_bound(req);
        if(sptr != s.end()) {
            // cout << "SPTR : " << *sptr << " " << S + *sptr << "\n";
            ans = min(ans, S + (*sptr));
        } 
    }
    cout << ans << "\n";

    return 0;
}
