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
OLD
does not pass all the time, but it is close. I feel like i've thought my idea thoroughly through and should step back and try another approach. still thinking about this problem. 

NEW
this problem is a good example of thinking about a problem on a different day. 

Got stuck and then thought about this problem for a while. 
When thinking about this problem for the second time, I used a bit more math to prove my answers and tried different ratios and stuff and proved that the current ratios 
weren't great. Then, after realizing that the best ratio was to split it in half, I realized that we should try to use parity to help us out. 

Originally, I was trying some heuristic approaches with some random optimizations and it wasn't going too great, but these optimizations did come in handy later. 
We just needed to make the parity observation

Suppose we partition into two groups. lhs and rhs, then we do roughly 7n / 4 queries, to see if elements are in either group or both groups. As we know 
exactly one group is missing, we know that one of the groups will have a number mismatch. Then, we have reduced this problem by narrowing the search down 
to roughly n / 4 elements and in a grid of size n vs 2n, then, we do the normal chop tricks from here and it works. 

We just needed to make the parity observation to get this to work. good thing i did not editorial i suppose. 
*/

int N;
vector<int> hidden;
int result;
int ask_cnt;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve(int interactor = false) {

    int n;
    if(interactor) {
        n = N;
    } else {
        cin >> n;
    }

    vector<int> idxs(n * 2 - 1);
    iota(idxs.begin(), idxs.end(), 0);
    shuffle(idxs.begin(), idxs.end(), rng);
    vector<int> val_ordering(n);
    iota(val_ordering.begin(), val_ordering.end(), 0);
    shuffle(val_ordering.begin(), val_ordering.end(), rng);

    auto ask = [&](vector<int> a, int x) -> int {
        ask_cnt++;
        vector<int> ta;
        for(int y : a) ta.push_back(idxs[y]);
        x = val_ordering[x];
        if(interactor) {
            int f = 0;
            for(int y : ta) {
                if(hidden[y] == x) f = 1;
            }
            return f;
        } else {
            cout << "? " << x + 1 << " " << ta.size();
            for(int y : ta) cout << " " << y + 1;
            cout << endl;
            int res; cin >> res;
            return res;
        }
    };

    //spend roughly 7n / 4 queries discerning where each number is at. 
    int med = n, total = n * 2 - 1;
    vector<int> left, right, both;
    vector<int> lo(med);
    iota(lo.begin(), lo.end(), 0);
    vector<int> hi(total - med);
    iota(hi.begin(), hi.end(), med);

    for(int i = 0; i < n; i++) {
        int response = ask(lo, i);
        if(response == 0) {
            right.push_back(i);
        } else {
            response = ask(hi, i);
            if(response == 1) {
                both.push_back(i);
            } else {
                left.push_back(i);
            }
        }
    }

    // cout << "left : " << left << " right : " << right << " both : " << both << endl;

    vector<int> cur, vals;
    if(left.size() * 2 + both.size() != med) {
        cur = lo;
        vals = left;
    } else if(right.size() * 2 + both.size() != total - med) {
        cur = hi;
        vals = right;
    } else {
        assert(0);
    }

    // cout << "cur : " << cur << " vals : " << vals << endl;

    auto chop = [&](auto self, int val, vector<int> cand_idxs) -> int {
        int sz = cand_idxs.size();
        if(sz == 1) {
            return 1;
        }

        vector<int> lhs(cand_idxs.begin(), cand_idxs.begin() + sz / 2), rhs(cand_idxs.begin() + sz / 2, cand_idxs.end());

        int response_left = ask(lhs, val);
        // 1/4 chance, check to the right
        if(response_left == 0) {
            return self(self, val, rhs);
        } else {
            int response_right = ask(rhs, val);
            // 1/2 chance, 
            if(response_right) {
                return 0;
            } else {
                return self(self, val, lhs);
            }
        }
    };

    for(int i = 0; i < vals.size(); i++) {
        if(chop(chop, vals[i], cur)) {
            int ans = val_ordering[vals[i]];
            if(interactor) {
                result = ans;
            } else {
                cout << "! " << ans + 1 << endl;
            }
            return;
        }
    }



    assert(0);

}

void test(int n) {
    hidden.assign(n * 2, 0);
    iota(hidden.begin(), hidden.begin() + n, 0);
    iota(hidden.begin() + n, hidden.end(), 0);
    shuffle(hidden.begin(), hidden.end(), rng);
    int solution = hidden.back();
    hidden.pop_back();
    N = n;
    ask_cnt = 0;

    solve(1);

    if(result != solution) {
        cout << "a test got a wrong solution!" << endl;
    } else {
        cout << "n : " << n << " ask_cnt : " << ask_cnt << " ratio : " << ((ld) ask_cnt) / n << endl;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 1; i <= 300; i++) test(i);
    // for(int i = 0; i < 20; i++) test(300);

    int casi; cin >> casi;
    while(casi-->0) solve();

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
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// does not pass all the time, but it is close. I feel like i've thought my idea thoroughly through and should step back and try another approach. still thinking about this problem. 

// */

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

// template<typename T, typename D>
// std::ostream& operator<<(std::ostream& os, map<T,D> m) {
//     for(auto &x: m) os << x.first << " " << x.second << " | ";
//     return os;
// }

// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// void solve() {

//     int n; cin >> n;
//     int sz = n * 2 - 1;
//     vector<int> a(sz);
//     iota(a.begin(), a.end(), 0);

//     auto interact = [&](vector<int> b, int x) -> bool {
//         // ops++;
//         // for(int c : b) if(hidden[c] == x) return 1;
//         // return 0;
//         cout << "? " << x + 1 << " " << b.size();
//         for(int c : b) cout << " " << c + 1;
//         cout << endl;
//         int res; cin >> res;
//         if(res == -1) assert(0);
//         return res;
//     };

//     set<int> clr;
//     auto chop = [&](auto self, int l, int r, int x) -> bool {
//         // cout << "l : " << l << " r : " << r << endl;
//         if(l + 1 == r) {
//             return 1;
//             clr.insert(l);
//         }
//         int mid = (l + r + 1) / 2;
//         vector<int> lhs(a.begin() + l, a.begin() + mid);
//         vector<int> rhs(a.begin() + mid, a.begin() + r);
//         int lval = interact(lhs, x);
//         // cout << "lval ? : " << lval << endl;
//         if(lval == 0) {
//             return self(self, mid, r, x);
//         }
//         int rval = interact(rhs, x);
//         if(rval) {
//             return 0;
//         }
//         return self(self, l, mid, x);
//     };

//     // int n = (sz + 1) / 2;
//     vector<int> cand(n);
//     iota(cand.begin(), cand.end(), 0);
//     shuffle(cand.begin(), cand.end(), rng);

//     for(int i = 0; i < n; i++) {
//         shuffle(a.begin(), a.end(), rng);
//         if(chop(chop, 0, a.size(), cand[i])) {
//             cout << "! " << cand[i] + 1 << endl;
//             return;
//         }
//         for(int j = ((int) a.size()) - 1; j >= 0; j--) {
//             if(clr.count(j)) {
//                 a.erase(a.begin() + j);
//             }
//         }
//         clr.clear();
//     }

// }

// int estimate_ops(int debug, vector<int> hidden) {

//     // cout << "hidden : " << hidden << '\n';
//     int n, sz;

//     if(!debug) {
//         cin >> n;
//         sz = n * 2 - 1;
//     } else {
//         sz =
//         hidden.size();
//     }

//     vector<int> a(sz);
//     iota(a.begin(), a.end(), 0);
//     shuffle(a.begin(), a.end(), rng);

//     int ops = 0;

//     map<array<int,2>, int> accounted;
//     auto interact = [&](vector<int> b, int x) -> bool {
//         ops++;
//         for(int c : b) if(hidden[c] == x) return 1;
//         return 0;
//     };

//     auto chop = [&](auto self, int l, int r, int x) -> bool {
//         //when called on range [l, r], we expect that there are 2 of this element in this range. 
//         if(l + 1 == r) {
//             return 1;
//         }

//         int mid = (l + r) / 2;

//         //case one of the sides is full, so we don't need to do any operations
//         if(accounted[{l,mid}] == mid - l) {
//             accounted[{mid, r}] += 2;
//             return self(self, mid, r, x);
//         }

//         if(accounted[{mid, r}] == r - mid) {
//             accounted[{l, mid}] += 2;
//             return self(self, l, mid, x);
//         }

//         int rem_lhs = (mid - l) - accounted[{l, mid}];
//         int rem_rhs = (r - mid) - accounted[{mid, r}];

//         vector<int> first(a.begin() + l, a.begin() + mid), second(a.begin() + mid, a.begin() + r);
//         array<int,2> first_r = {l, mid}, second_r = {mid, r};

//         if(rem_lhs > rem_rhs) {
//             swap(first, second);
//             swap(first_r, second_r);
//         }

//         int first_val = interact(first, x);
//         accounted[first_r] += first_val;

//         //try to avoid as many of these cases as possible
//         if(first_val == 0) {
//             accounted[second_r] += 2;
//             return self(self, second_r[0], second_r[1], x);
//         }

//         int second_val = interact(second, x);
//         accounted[second_r] += second_val;

//         if(second_val) {
//             return 0;
//         }

//         //try to avoid as many of these cases as possible
//         accounted[first_r]++;
//         return self(self, first_r[0], first_r[1], x);
//     };

//     n = (sz + 1) / 2;

//     vector<int> cand(n - 1);
//     iota(cand.begin(), cand.end(), 0);
//     shuffle(cand.begin(), cand.end(), rng);
//     cand.push_back(n - 1);

//     // vector<int> cand(n);
//     // iota(cand.begin(), cand.end(), 0);
//     // shuffle(cand.begin(), cand.end(), rng);

//     for(int i = 0; i < n; i++) {
//         // shuffle(a.begin(), a.end(), rng);
//         if(chop(chop, 0, a.size(), cand[i])) {
//             if(cand[i] != n - 1) {
//                 cout << "i : " << i << endl;
//                 cout << "a : " << a << endl;
//                 cout << "hidden : " << hidden << endl;
//                 cout << "cand : " << cand << endl;;
//                 cout << "accounted : " << accounted << endl;
//                 assert(cand[i] == n - 1);
//             }
//             // cout << "cand found : " << cand[i] << '\n';
//             return ops;
//         }
//         for(auto [k, v] : accounted) {
//             if(!(k[1] - k[0] >= v)) {
//                 cout << "i : " << i << endl;
//                 cout << "hidden : " << hidden << endl;
//                 cout << "cand : " << cand << endl;;
//                 cout << "accounted : " << accounted << endl;
//                 assert(k[1] - k[0] >= v);
//             }

//             //sanity check, is wayy too sane. 
//             // int cnt = 0;
//             // for(int j = 0; j <= i; j++) {
//             //     for(int l = k[0]; l < k[1]; l++) {
//             //         if(hidden[l] == cand[j]) cnt++;
//             //     }
//             // }
//             // if(cnt != v) {
//             //     cout << "k : " << k << " v : " << v << " cnt got : " << cnt << endl;
//             //     cout << "i : " << i << endl;
//             //     cout << "hidden : " << hidden << endl;
//             //     cout << "cand : " << cand << endl;;
//             //     cout << "accounted : " << accounted << endl;
//             //     assert(0);
//             // }
//         }
//     }

//     assert(0);

// }

// int total_tests = 0, bad_cnt = 0;

// void test(int n, int strict) {
//     vector<int> a(n * 2 - 1);
//     iota(a.begin(), a.begin() + n, 0);
//     iota(a.begin() + n, a.end(), 0);
//     shuffle(a.begin(), a.end(), rng);

//     int target = n * 4 + 2 * (31 - __builtin_clz(n - 1));
//     int actual = estimate_ops(1, a);

//     cout << "n : " << n << " target : " << target << " actual ops : " << actual << '\n';

//     if(strict) {
//         assert(actual <= target);
//     }

//     total_tests++;
//     if(actual > target) bad_cnt++;

// }

// ll choose2(ll n) {
//     return n * (n - 1) / 2;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     // for(int i = 1; i <= 300; i++) test(i, 0);
//     // for(int i = 1; i <= 300; i++) test(i, 1);
//     // for(int j = 0; j < 10; j++) for(int i = 1; i <= 300; i++) test(i, 0);

//     // for(int i = 1; i <= 300; i++) {
//     //     bad_cnt = 0;
//     //     total_tests = 0;
//     //     for(int j = 1; i * j <= 5000; j++) test(i, 0);
//     //     if(bad_cnt) cout << "i : " << i << " bad_cnt : " << bad_cnt << " total_tests : " << total_tests << '\n';
//     // }

//     // int n = 300;

//     // ll num = choose2(2 * n - 1) - (choose2(n) + choose2(n - 1));
//     // ll den = choose2(2 * n - 1);

//     // cout << "prob of being in same : " << ((ld) num) / den << '\n';

//     for(int i = 0; i < 50; i++) test(300, 0);

//     // cout << "bad : " << bad_cnt << " total : " << total_tests << '\n';

//     // int casi; cin >> casi;
//     // while(casi-->0) solve();

//     return 0;
// }