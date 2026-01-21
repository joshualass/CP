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
lots of impl hell and casework for the hard version

moral of the story - write a program to help you find the optimal partitions, although it is not easy to see this
this takes some extra work, but helps with the worst case

thought of this after trying to remove as much casework as possible. 

very nice problem, where you once again have to use every piece of information. 

You partition the group into two groups
for one group, you don't have any information really, we denote it as the true group
for the other group, we know that if the selected integer is in this group, then the answer to the previous question is false. 
Then, for our next guess, we p much chop the true and false group and half and guess that. 
Regardless of verdict, half the false group will go bye bye, and half the current true will be the next false. 

Make sure to offset optimally ....

Clean ...
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> t(n), f;
    iota(t.begin(), t.end(), 1);

    int ask_cnt = 0;

    auto guess = [&](vector<int> a) -> int {
        cout << "? " << a.size();
        for(int x : a) cout << " " << x;
        cout << endl;
        ask_cnt++;
        string res; cin >> res;
        return res == "YES";
    };

    auto finish = [&](vector<int> a) -> void {
        for(int x : a) {
            cout << "! " << x << endl;
            string res; cin >> res;
            if(res == ":)") return;
        }
        assert(0);
    };

    while(t.size() + f.size() >= 3) {
        int te = -1, fe = -1;
        array<int,2> best = {INT_MAX, INT_MAX};
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 2; j++) {

                int t1 = (t.size() + i) / 2, f1 = (f.size() + j) / 2;
                int t2 = t.size() - t1, f2 = f.size() - f1;

                array<int,2> nxt = {t1 + t2 + f1, t1 + f1};
                array<int,2> nxf = {t1 + t2 + f2, t2 + f2};
                auto zzz = max(nxt, nxf);
                if(zzz < best) {
                    best = zzz;
                    te = t1;
                    fe = f1;
                }
            }
        }
        
        vector<int> test(t.begin(), t.begin() + te);
        test.insert(test.end(), f.begin(), f.begin() + fe);
        int res = guess(test);
        vector<int> nxt, nxf;
        if(res) {
            nxt = test;
            nxf = vector<int>(t.begin() + te, t.end());
        } else {
            nxt = vector<int>(t.begin() + te, t.end());
            nxt.insert(nxt.end(), f.begin() + fe, f.end());
            nxf = vector<int>(t.begin(), t.begin() + te);
        }
        t = nxt;
        f = nxf;
    }

    t.insert(t.end(), f.begin(), f.end());
    finish(t);

    return 0;
}


// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

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

// void calc_ops() {
//     ld n = 1e5;
//     int ops = 0;
//     // while(n > 1) {
//     //     n *= 3.0/4.0;
//     //     ops += 2;
//     // }

//     // while(n > 1) {
//     //     n *= 2.0/3.0;
//     //     ops += 3;
//     // }
    
//     while(n > 1) {
//         n *= 4.0/5.0;
//         ops += 1;
//     }

//     cout << ops << '\n';
// }

// const int debug = 0;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     // calc_ops();

//     int n; cin >> n;
//     // vector<int> a(n);
//     // iota(a.begin(), a.end(), 1);
//     vector<int> t(n), f;
//     iota(t.begin(), t.end(), 1);

//     int ask_cnt = 0;

//     auto guess = [&](vector<int> a) -> int {
//         cout << "? " << a.size();
//         for(int x : a) cout << " " << x;
//         cout << endl;
//         ask_cnt++;
//         if(debug) {
//             // return rand() & 1;
//             if(a.size() <= 1) return 1;
//             return 0;
//         } else {
//             string res; cin >> res;
//             return res == "YES";
//         }
//     };

//     auto finish = [&](vector<int> a) -> void {
//         for(int x : a) {
//             cout << "! " << x << endl;
//             if(debug) {
//                 // ask_cnt++;
//             } else {
//                 string res; cin >> res;
//                 if(res == ":)") return;
//             }
//         }
//         if(debug) return;
//         assert(0);
//     };

//     while(t.size() + f.size() >= 3) {
//         int te = -1, fe = -1;
//         array<int,2> best = {INT_MAX, INT_MAX};
//         for(int i = 0; i < 3; i++) {
//             for(int j = 0; j < 2; j++) {

//                 int t1 = (t.size() + i) / 2, f1 = (f.size() + j) / 2;
//                 int t2 = t.size() - t1, f2 = f.size() - f1;

//                 array<int,2> nxt = {t1 + t2 + f1, t1 + f1};
//                 array<int,2> nxf = {t1 + t2 + f2, t2 + f2};
//                 auto zzz = max(nxt, nxf);
//                 if(zzz < best) {
//                     best = zzz;
//                     te = t1;
//                     fe = f1;
//                 }
//             }
//         }

//         // cout << "ts : " << t.size() << " fs : " << f.size() << " te : " << te << " fe : " << fe << endl;
//         // cout << "best : " << best << endl;
        
//         vector<int> test(t.begin(), t.begin() + te);
//         test.insert(test.end(), f.begin(), f.begin() + fe);
//         int res = guess(test);
//         vector<int> nxt, nxf;
//         if(res) {
//             nxt = test;
//             nxf = vector<int>(t.begin() + te, t.end());
//         } else {
//             nxt = vector<int>(t.begin() + te, t.end());
//             nxt.insert(nxt.end(), f.begin() + fe, f.end());
//             nxf = vector<int>(t.begin(), t.begin() + te);
//         }
//         t = nxt;
//         f = nxf;
//     }

//     t.insert(t.end(), f.begin(), f.end());
//     finish(t);

//     // while(1) {
//     //     if(t.size() + f.size() <= 3) {
//     //         // cout << "f : " << f << " t : " << t << "\n";
//     //         // cout << "ask count at end : " << ask_cnt << '\n';
//     //         vector<int> a = t;
//     //         a.insert(a.end(), f.begin(), f.end());

//     //         // cout << "a : " << a << '\n';

//     //         if(t.size() == 2 && f.size() == 1) {
//     //         // if(0) {
//     //             // if(n == 99979) {
//     //             //     cout << "ac:" << ask_cnt << endl;    
//     //             //     assert(0);
//     //             // }
//     //             int res2 = guess({a[0], a[1]});
//     //             if(res2) {
//     //                 finish({a[0], a[1]});
//     //             } else {
//     //                 int res3 = guess({a[0], a[2]});
//     //                 if(res3) {
//     //                     finish({a[0], a[2]});
//     //                 } else {
//     //                     finish({a[1], a[2]});
//     //                 }
//     //             }
//     //         } else {
//     //             while(1) {
//     //                 if(a.size() <= 3) {
//     //                     if(a.size() <= 2) {
//     //                         finish(a);
//     //                     } else {
//     //                         int res = guess({a[0], a[1]});
//     //                         if(res) {
//     //                             int res2 = guess({a[0], a[1]});
//     //                             if(res2) {
//     //                                 finish({a[0], a[1]});
//     //                             } else {
//     //                                 int res3 = guess({a[0], a[2]});
//     //                                 if(res3) {
//     //                                     finish({a[0], a[2]});
//     //                                 } else {
//     //                                     finish({a[1], a[2]});
//     //                                 }
//     //                             }
//     //                         } else {
//     //                             int res2 = guess({a[0], a[2]});
//     //                             if(res2) {
//     //                                 finish({a[0], a[2]});
//     //                             } else {
//     //                                 finish({a[1], a[2]});
//     //                             }
//     //                         }
//     //                     }
//     //                     break;
//     //                 } else {
//     //                     int one = (a.size() + 3) / 4;
//     //                     int two = one + (a.size() + 2) / 4;
//     //                     int three = two + (a.size() + 1) / 4;
//     //                     vector<int> first(a.begin(), a.begin() + one), second(a.begin(), a.begin() + one);
//     //                     first.insert(first.end(), a.begin() + one, a.begin() + two);
//     //                     second.insert(second.end(), a.begin() + two, a.begin() + three);
            
//     //                     int res1 = guess(first);
//     //                     int res2 = guess(second);
//     //                     if(res1) {
//     //                         if(res2) {
//     //                             a.erase(a.begin() + three, a.end());
//     //                         } else {
//     //                             a.erase(a.begin() + two, a.begin() + three);
//     //                         }
//     //                     } else {
//     //                         if(res2) {
//     //                             a.erase(a.begin() + one, a.begin() + two);
//     //                         } else {
//     //                             a.erase(a.begin(), a.begin() + one);
//     //                         }
//     //                     }
//     //                 }
//     //             }
//     //         }

//     //         break;
//     //     } else {
//     //         int te = -1, fe = -1;
//     //         array<int,2> best = {INT_MAX, INT_MAX};
//     //         for(int i = 0; i < 2; i++) {
//     //             for(int j = 0; j < 2; j++) {

//     //                 int nxt1 = t.size() + (f.size() + j) / 2;
//     //                 int nxt2 = (t.size() + i) / 2 + (f.size() + j) / 2;

//     //                 int nxf1 = t.size() + (f.size() - (f.size() + j) / 2);
//     //                 int nxf2 = (t.size() - (t.size() + i) / 2) + (f.size() - (f.size() + j) / 2);

//     //                 array<int,2> nxt = {nxt1, nxt2};
//     //                 array<int,2> nxf = {nxf1, nxf2};
//     //                 auto zzz = max(nxt, nxf);
//     //                 if(zzz < best) {
//     //                     best = zzz;
//     //                     te = i;
//     //                     fe = j;
//     //                 }
//     //             }
//     //         }
            
//     //         vector<int> test(t.begin(), t.begin() + (t.size() + te) / 2);
//     //         test.insert(test.end(), f.begin(), f.begin() + (f.size() + fe) / 2);
//     //         int res = guess(test);
//     //         vector<int> nxt, nxf;
//     //         if(res) {
//     //             nxt = test;
//     //             nxf = vector<int>(t.begin() + (t.size() + te) / 2, t.end());
//     //         } else {
//     //             nxt = vector<int>(t.begin() + (t.size() + te) / 2, t.end());
//     //             nxt.insert(nxt.end(), f.begin() + (f.size() + fe) / 2, f.end());
//     //             nxf = vector<int>(t.begin(), t.begin() + (t.size() + te) / 2);
//     //         }
//     //         t = nxt;
//     //         f = nxf;
//     //     }
//     // }
    
//     if(debug) {
//         cout << "ask cnt : " << ask_cnt << endl;
//     }

//     return 0;
// }
