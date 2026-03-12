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

    vector<int> a(6);
    for(int &x : a) cin >> x;

    auto eval = [&](int hash) -> ld {
        map<int,int> m;
        for(int i = 0; i < 6; i++) {
            int cnt = hash % 6;
            m[a[i]] += cnt;
            hash /= 6;
        }
        int res = 0;
        for(auto [k, v] : m) res = max(res, k * v);
        return res;
    };

    vector<map<int,ld>> dp(4);

    vector<int> z(1, 1);
    for(int i = 1; i < 7; i++) z.push_back(z.back() * 6);
    
    auto dfs = [&](auto self, int roll, int hash) -> ld {
        if(dp[roll].count(hash) == 0) {
            if(roll == 3) {
                dp[roll][hash] = eval(hash);
            } else {
                int cnt = 0;
                int t = hash;
                for(int i = 0; i < 6; i++) {
                    cnt += t % 6;
                    t /= 6;
                }
                int left = 5 - cnt;
                ld ev = 0;
                for(int i = 0; i < z[left]; i++) {
                    ld best = 0;
                    for(int bm = 0; bm < 1 << left; bm++) {
                        int nx_hash = hash;
                        for(int j = 0; j < left; j++) {
                            if((bm >> j) & 1) {
                                nx_hash += z[((i / z[j]) % 6)];
                            }
                        }
                        best = max(best, self(self, roll + 1, nx_hash));
                    }
                    ev += best;
                }
                dp[roll][hash] = ev / z[left];
            }
        }
        return dp[roll][hash];
    };

    cout << fixed << setprecision(10) << dfs(dfs, 0, 0) << '\n';

    return 0;
}


// #include <algorithm>
// #include <bitset>
// #include <complex>
// #include <deque>
// #include <exception>
// #include <fstream>
// #include <functional>
// #include <iomanip>
// #include <ios>
// #include <iosfwd>
// #include <iostream>
// #include <istream>
// #include <iterator>
// #include <limits>
// #include <list>
// #include <locale>
// #include <map>
// #include <memory>
// #include <new>
// #include <numeric>
// #include <ostream>
// #include <queue>
// #include <set>
// #include <sstream>
// #include <stack>
// #include <stdexcept>
// #include <streambuf>
// #include <string>
// #include <typeinfo>
// #include <utility>
// #include <valarray>
// #include <vector>
// #include <array>
// #include <atomic>
// #include <chrono>
// #include <condition_variable>
// #include <forward_list>
// #include <future>
// #include <initializer_list>
// #include <mutex>
// #include <random>
// #include <ratio>
// #include <regex>
// #include <scoped_allocator>
// #include <system_error>
// #include <thread>
// #include <tuple>
// #include <typeindex>
// #include <type_traits>
// #include <unordered_map>
// #include <unordered_set>
// #include <cassert>
// #include <cstring>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     // {hashed state, for each set of things to keep, the reachable states from that}
//     map<int, vector<vector<int>>> pc;

//     //gets int hash of a
//     auto get_hash = [&](array<int,5> a) -> int {
//         vector<int> cnts(6);
//         for(int x : a) cnts[x]++;
//         int res = 0;
//         int mul = 1;
//         for(int i = 0; i < 6; i++) {
//             res += cnts[i] * mul;
//             mul *= 6;
//         }
//         return res;
//     };

//     vector<int> a(6);
//     for(int &x : a) cin >> x;

//     //gets ev from a hash value final state. 
//     auto get_value = [&](int hash) -> ld {
//         vector<int> cnts(6);
//         int res = 0;
//         map<int,int> m;
//         for(int i = 0; i < 6; i++) {
//             int c = hash % 6;
//             hash /= 6;
//             m[a[i]] += c;
//         }
//         for(auto [k, v] : m) res = max(res, k * v);
//         // cout << "hash : " << hash << " res : " << res << '\n';
//         return res;
//     };

//     auto correct_visit_states = [&](int hash) -> vector<int> {



//     };

//     auto visit_states = [&](array<int,5> curr, int bm) -> vector<int> {
//         //bm stores which set of things we are keeping from curr
//         vector<int> out;
//         for(int i = 0; i < 5; i++) {
//             if(((bm >> i) & 1) == 0) {
//                 out.push_back(i);
//             }
//         }
        
//         vector<int> states;
//         int p = 1;
//         for(int i = 0; i < out.size(); i++) p *= 6;
//         for(int i = 0; i < p; i++) {
//             int t = i;
//             for(int j = 0; j < out.size(); j++) {
//                 curr[out[j]] = t % 6;
//                 t /= 6;
//             }
//             states.push_back(get_hash(curr));
//         }
//         return states;
//     };

//     for(int i = 0; i < 6 * 6 * 6 * 6 * 6; i++) {
//         array<int,5> a = {};
//         int t = i;
//         for(int j = 0; j < 5; j++) {
//             a[j] = t % 6;
//             t /= 6;
//         }
//         int val = get_hash(a);
//         // cout << "i : " << i << " a : " << a << '\n';
//         if(pc.count(val)) continue;
//         for(int j = 0; j < 1 << 5; j++) {
//             vector<int> t = visit_states(a, j);
//             // if(i == 0 && t == vector<int>{38880}) {
//             //     cout << "i : " << i << " j : " << j << " t : " << t << '\n';
//             // }
//             pc[val].push_back(t);
//         }
//     }

//     vector<map<int,ld>> dp(4);
//     auto dfs = [&](auto self, int roll, int hash) -> ld {
//         if(dp[roll].count(hash) == 0) {
//             if(roll == 3) dp[roll][hash] = get_value(hash);
//             else {
//                 ld res = 0;
//                 for(auto state_set : pc[hash]) {
//                     ld ev = 0;
//                     for(auto nx_hash : state_set) {
//                         ev += self(self, roll + 1, nx_hash);
//                     }
//                     ev /= state_set.size();
//                     if(abs(ev - 30) <= 1e-10 && hash != 38880) {
//                         // cout << "hash gets this : " << hash << endl;
//                         // cout << " good state set with good things : " << state_set << endl;
//                         assert(0);
//                     }
//                     res = max(res, ev);
//                 }
//                 // cout << "roll : " << roll << " hash : " << hash << " res : " << res << '\n';
//                 dp[roll][hash] = res;
//             }
//         }
//         return dp[roll][hash];
//     };

//     array<int,5> trash = {};
//     vector<int> starts = visit_states(trash, 0);

//     cout << "starts : " << starts << '\n';

//     ld res = 0;
//     for(auto start : starts) {
//         res += dfs(dfs, 1, start);
//     }

//     cout << fixed << setprecision(10) << res / starts.size() << '\n';

//     // vector<map<array<int,5>, ld>> dp(4);

//     // auto recur = [&](auto self, int roll, array<int,5> state) -> ld {
//     //     sort(state.begin(), state.end());
//     //     if(dp[roll].count(state) == 0) {
//     //         if(roll == 3) {
//     //             map<int,int> m;
//     //             for(int i = 0; i < 5; i++) {
//     //                 m[a[state[i]]]++;
//     //             }
//     //             int res = 0;
//     //             for(auto [k, v] : m) {
//     //                 res = max(res, k * v);
//     //             }
//     //             dp[roll][state] = res;
//     //         } else {
//     //             ld best_ev = 0;
//     //             for(int keep = 0; keep < 1 << 5; keep++) {
//     //                 vector<array<int,5>> states;
//     //                 array<int,5> curr_state = state;
//     //                 auto dfs = [&](auto dfsself, int i) -> void {
//     //                     if(i == 5) {
//     //                         states.push_back(curr_state);
//     //                         return;
//     //                     }
//     //                     if((keep >> i) & 1) {
//     //                         dfsself(dfsself, i + 1);
//     //                     } else {
//     //                         for(int j = 0; j < 6; j++) {
//     //                             curr_state[i] = j;
//     //                             dfsself(dfsself, i + 1);
//     //                         }
//     //                     }
//     //                 };

//     //                 dfs(dfs, 0);

//     //                 ld total = states.size();
//     //                 ld ev = 0;
//     //                 for(auto st : states) {
//     //                     ev += self(self, roll + 1, st);
//     //                 }
//     //                 ev /= total;
//     //                 best_ev = max(best_ev, ev);
//     //             }
//     //             dp[roll][state] = best_ev;
//     //         }
//     //     }
//     //     return dp[roll][state];
//     // };

//     // vector<array<int,5>> states;
//     // array<int,5> curr_state = {};
//     // int keep = 0;

//     // auto dfsstart = [&](auto dfsself, int i) -> void {
//     //     if(i == 5) {
//     //         states.push_back(curr_state);
//     //         return;
//     //     }
//     //     if((keep >> i) & 1) {
//     //         dfsself(dfsself, i + 1);
//     //     } else {
//     //         for(int j = 0; j < 6; j++) {
//     //             curr_state[i] = j;
//     //             dfsself(dfsself, i + 1);
//     //         }
//     //     }
//     // };

//     // dfsstart(dfsstart, 0);

//     // ld res = 0;
//     // for(auto st : states) {
//     //     res += recur(recur, 1, st);
//     // }

//     // cout << fixed << setprecision(10) << res / states.size() << '\n';

//     return 0;
// }
