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

/*
first thing is that parity is off at the end, which we didn't account for

=> maybe we are not at the end yet, but the parity is off. 
it is ok to end a little earlier so that parity is better and it is the same ... 

This leads to the dp state. 

This problem is randomly rated 3000
The first thing to observe is that we should always greedily choose any matching cards to get a coin when we can. 
we cannot get a coin when all the elements are unique. We should try to avoid this as much as possible. 
A way to do this is to choose a pair of nodes so that the next time will be the furthest time until unique. 
However, we also want to take into consideration the parity of the remaining elements. Thus, we need to be careful 
about which elements we choose at the end. Additionally, it might not be optimal to choose the latest one that makes everything
distinct. 

This leads us to do a dynamic programming approach. 
Let dp[i] => the most number of coins we can have such that after picking up the i'th coin, all the cards are distinct. 
We need to do 3 things
1) set the starting dp state or find it's never reachable
2) handle transitions between dp states, we can transition on the first occurrence of an unrepeated element
3) calculate score when choosing a pair that makes it to the end. 

Do the above and you are good. 

*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    vector<int> b(k), dp(n + 1, -1e9);
    for(int i = 0; i < k; i++) {
        b[a[i]]++;
    }

    int start = 0, p = k;
    
    while(p < n) {
        int f = -1;
        for(int i = 0; i < k; i++) {
            if(b[i] >= 2) f = i;
        }
        if(f == -1) break;
        b[f] -= 2;
        b[a[p++]]++;
        b[a[p++]]++;
        start++;
    }

    if(p == n) { //make it through
        for(int i = 0; i < k; i++) start += b[i] / 2;
        cout << start << '\n';
    } else { //don't make it through
        dp[p] = start;
        int res = 0;
        for(int i = k; i <= n; i += 2) {
            // cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
            set<int> s;
            set<array<int,2>> pv;
            for(int j = i; j < n; j += 2) {
                if(s.count(a[j])) {
                    s.erase(a[j]);
                } else {
                    s.insert(a[j]);
                }
                if(s.count(a[j+1])) {
                    s.erase(a[j+1]);
                } else {
                    s.insert(a[j+1]);
                }
                if(s.size() == 2) {
                    array<int,2> c = {*s.begin(), *++s.begin()};
                    if(pv.count(c) == 0) {
                        dp[j + 2] = max(dp[j + 2], dp[i] + (j - i) / 2);
                    }
                    pv.insert(c);
                }
            }
            // cout << "pv : " << pv << '\n';
            vector<int> rem(k);
            for(int j = i; j < n; j++) rem[a[j]]++;
            vector<int> odd, even;
            // cout << "rem : " << rem << '\n';
            int score = 0;
            for(int j = 0; j < k; j++) {
                if(rem[j] & 1) {
                    odd.push_back(j);
                } else {
                    even.push_back(j);
                }
                score += (rem[j] + 1) / 2;
            }
            // cout << "even : " << even << '\n';
            // cout << "odd : " << odd << '\n';
            //try to do as much evens as we can 2
            int f = 0;
            for(int i = 0; i < even.size() && f == 0; i++) {
                for(int j = i + 1; j < even.size() && f == 0; j++) {
                    if(pv.count({even[i], even[j]}) == 0) {
                        f = 1;
                    }
                }
            }
            if(f) {
                // cout << "f is true for 2 even!\n";
                res = max(res, dp[i] + score - 0);
            }
            //try to do as much evens as we can 1
            for(int i = 0; i < even.size() && f == 0; i++) {
                for(int j = 0; j < odd.size() && f == 0; j++) {
                    if(pv.count({min(even[i], odd[j]), max(even[i], odd[j])}) == 0) {
                        f = 1;
                    }
                }
            }
            if(f) {
                // cout << "f is true for 1 even!\n";
                res = max(res, dp[i] + score - 1);
            }
            for(int i = 0; i < odd.size() && f == 0; i++) {
                for(int j = i + 1; j < odd.size() && f == 0; j++) {
                    if(pv.count({odd[i], odd[j]}) == 0) {
                        f = 1;
                    }
                }
            }
            if(f) {
                // cout << "f is true for 0 even!\n";
                res = max(res, dp[i] + score - 2);
            }
        }

        cout << res << '\n';
    }

    // int n, k; cin >> n >> k;
    // vector<int> a(n);
    // for(int &x : a) {
    //     cin >> x;
    //     x--;
    // }

    // vector<int> b(k);
    // for(int i = 0; i < k; i++) {
    //     b[a[i]]++;
    // }

    // int p = k;
    // int before = 0;
    // int res = 0;
    // int cnt = 0;

    // while(p != n) {
    //     int f = -1;
    //     for(int i = 0; i < k; i++) {
    //         if(b[i] >= 2) {
    //             f = i;
    //         }
    //     }

    //     if(f == -1) {
    //         set<array<int,2>> unvis;
    //         for(int i = 0; i < k; i++) {
    //             for(int j = i + 1; j < k; j++) unvis.insert({i, j});
    //         }

    //         set<int> s;
    //         array<int,2> start = {-1,-1};

    //         for(int i = p; i < n; i++) {
    //             if(s.count(a[i])) {
    //                 s.erase(a[i]);
    //             } else {
    //                 s.insert(a[i]);
    //             }
    //             if(s.size() == 2) {
    //                 array<int,2> c = {*s.begin(), *++s.begin()};
    //                 unvis.erase(c);
    //                 start = c;
    //                 if(unvis.empty()) {
    //                     break;
    //                 }
    //             }
    //         }
    //         if(unvis.size()) {
    //             vector<int> rem(k);
    //             for(int i = p; i < n; i++) rem[a[i]]++;
    //             // cout << "rem : " << rem << '\n';

    //             int cur = 0;
    //             for(int i = 0; i < k; i++) cur += (rem[i] + 1) / 2;

    //             for(auto uv : unvis) {
    //                 int test = cur;
    //                 test -= (rem[uv[0]] + 1) / 2;
    //                 test -= (rem[uv[1]] + 1) / 2;
    //                 test += rem[uv[0]] / 2;
    //                 test += rem[uv[1]] / 2;
    //                 res = max(res, before + test);
    //             }

    //             cnt++;

    //             if(cnt >= 5) break;

    //             start = {0,1};
    //             for(int i = 0; i < k; i++) {
    //                 for(int j = i + 1; j < k; j++) {
    //                     int sp = (rem[start[0]] & 1) + (rem[start[1]] & 1);
    //                     // cout << "start : " << start << " sp : " << sp << '\n';
    //                     int np = (rem[i] & 1) + (rem[j] & 1);
    //                     // cout << "uv : " << uv << " np : " << np << '\n';
    //                     if(np < sp) start = {i, j};
    //                 }
    //             }
    //         }

    //         // cout << "p : " << p << " start : " << start << '\n';

    //         b[start[0]]--;
    //         b[start[1]]--;
    //     } else {
    //         before++;
    //         b[f] -= 2;
    //     }
    //     b[a[p++]]++;
    //     b[a[p++]]++;
    // }

    // // cout << "res : " << res << '\n';
    // // cout << "cnt : " << cnt << '\n';

    // for(int x : b) before += x / 2;
    // cout << max(res, before) << '\n';

    return 0;
}
