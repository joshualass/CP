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

// /*

// transform the coordinates, they say ...

// */

// template<typename T>
// struct Tree {
//     static constexpr T base = {INT_MIN, INT_MIN};
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return max(a, b);
//     }
//     Tree(int n, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = f(v[curr], val);
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = f(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = f(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return f(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, d; cin >> n >> d;
//     vector<array<int,2>> res(n, {INT_MAX, INT_MAX});
//     vector<array<int,3>> a(n);
//     for(int i = 0; i < n; i++) {
//         cin >> a[i][0] >> a[i][1];
//         a[i][2] = i;
//     }

//     auto solve = [&]() -> void {

//         {
//             vector<array<int,4>> ta(n);
//             for(int i = 0; i < n; i++) {
//                 auto [x, y, id] = a[i];
//                 ta[i] = {x - y, x + y, id, x};
//             }
//             set<int> ys;
//             for(auto &x : ta) ys.insert(x[1]);
//             int p = 0;
//             map<int,int> m;
//             for(int y : ys) m[y] = p++;

//             //sort by transformed x. 
//             sort(ta.begin(), ta.end());

//             Tree<array<int,2>> tree(p);
//             p = 0;

//             for(int i = 0; i < n; i++) {
//                 while(ta[p][0] + d <= ta[i][0]) {
//                     tree.update(m[ta[p][1]], {ta[p][3], ta[p][2]});
//                     p++;
//                 }
//                 auto [x, id] = tree.query(0, m[a[i][1]] + 1);
//                 array<int,2> cand = {ta[i][3] - x, -id};

//             }


//         }

//     };

//     auto rotate = [&]() -> void {
//         for(int i = 0; i < n; i++) {
//             swap(a[i][0], a[i][1]);
//             a[i][1] *= -1;
//         }
//     };

//     for(int i = 0; i < 4; i++) {
//         solve();
//         rotate();
//     }

//     // for(int i = 0; i < 2; i++) {
//     //     solve();
//     //     rotate();
//     // }

//     for(int i = 0; i < n; i++) cout << (res[i][1] == INT_MAX ? -1 : res[i][1]) << " \n"[i == n - 1];    

//     return 0;
// }


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

void insert(int y, int coord, int id, map<int,array<int,2>> &m) {
 
    auto it = m.upper_bound(y);
    if(it != m.begin()) {
        it--;
        auto [prev_coord, prev_id] = it->second;
        if(coord < prev_coord || coord == prev_coord && id > prev_id) return;
    }
 
    m[y] = {coord, id};
    it = m.upper_bound(y);
 
    while(it != m.end()) {
        auto [next_coord, next_id] = it->second;
        if(next_coord < coord || next_coord == coord && next_id > id) {
            it = m.erase(it);
        } else {
            break;
        }
    }
 
}

// void insert(int y, int coord, int id, map<int,array<int,2>> &m) {

//     auto it = m.upper_bound(y);
//     if(it != m.begin()) {
//         auto prev = std::prev(it);
//         auto [prev_coord, prev_id] = prev->second;
//         if(coord < prev_coord || coord == prev_coord && id > prev_id) return;
//     }

//     // m[y] = {coord, id};
//     // it = m.upper_bound(y);

//     it = m.emplace_hint(it, y, array<int,2>{coord, id});
//     auto nxt = std::next(it);

//     while(nxt != m.end()) {
//         auto [next_coord, next_id] = nxt->second;
//         if(next_coord < coord || next_coord == coord && next_id > id) {
//             nxt = m.erase(nxt);
//         } else {
//             break;
//         }
//     }

// }

struct Tree {
    static constexpr array<int,2> base = {INT_MIN, -1};
    vector<map<int,array<int,2>>> v;
    int n, size;
    array<int,2> f(array<int,2> a, array<int,2> b) { //change this when doing maximum vs minimum etc.
        if(a[0] > b[0]) return a;
        if(a[0] < b[0]) return b;
        if(a[1] < b[1]) return a;
        return b;
    }
    Tree(int n) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {});
    }
    void update(int pos, int y, int coord, int id) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;

        while(1) {
            insert(y, coord, id, v[curr]);
            if(curr == 1) break;
            curr /= 2;
        }
    }
    array<int,2> query(int l, int r, int r2) {//queries in range [l,r)
        return _query(1,0,size,l,r, r2);
    }
    array<int,2> _query(int idx, int currl, int currr, int &targetl, int &targetr, int r2) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) {
            auto it = v[idx].lower_bound(r2);
            if(it != v[idx].begin()) {
                it--;
                return it->second;
            } else {
                return base;
            }
        }
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr, r2),
            _query(idx * 2 + 1, mid, currr, targetl, targetr, r2)
        );
    }
};

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d; cin >> n >> d;
    vector<array<int,2>> res(n, {INT_MAX, INT_MAX});
    vector<array<int,3>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    auto solve = [&]() -> void {

        sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
            return lhs[0] + lhs[1] < rhs[0] + rhs[1];
        });

        // cout << "a : " << a << '\n';

        set<int> xs;
        for(int i = 0; i < n; i++) xs.insert(a[i][0]);
        map<int,int> m;
        int p = 0;
        for(int x : xs) m[x] = p++;

        Tree tree(p);

        p = 0;
        for(int i = 0; i < n; i++) {
            auto [x, y, id] = a[i];
            int cur_coord = x + y;
            while(a[p][0] + a[p][1] + d <= cur_coord) {
                auto [px, py, pid] = a[p];
                tree.update(m[px], py, px + py, pid);
                p++;
            }
            auto [coord, id_q] = tree.query(0, m[x] + 1, y + 1);
            // cout << "i : " << i << " a[i] : " << a[i] << " query coord : " << coord << " id " << id_q << '\n';
            
            if(id_q != -1) {
                assert(x + y - coord >= d);
                res[id] = min(res[id], {x + y - coord, id_q});
            }

        }
    };

    auto rotate = [&]() -> void {
        for(int i = 0; i < n; i++) {
            swap(a[i][0], a[i][1]);
            a[i][1] *= -1;
        }
    };

    for(int i = 0; i < 4; i++) {
        solve();
        rotate();
    }

    // for(int i = 0; i < 2; i++) {
    //     solve();
    //     rotate();
    // }

    for(int i = 0; i < n; i++) cout << (res[i][1] == INT_MAX ? -1 : res[i][1]) << " \n"[i == n - 1];

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

// template<typename T>
// struct Tree {
//     // {coord, id}
//     static constexpr T base = {INT_MAX,INT_MAX};
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         if(a[0] < b[0]) return a;
//         if(a[0] > b[0]) return b;

//         if(a[1] < b[1]) return a;
//         return b;
//     }
//     Tree(int n, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = f(v[curr], val);
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = f(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = f(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return f(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

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

//     int n, d; cin >> n >> d;
//     vector<array<int,2>> res(n, {INT_MAX, INT_MAX});
//     vector<array<int,3>> a(n);
//     for(int i = 0; i < n; i++) {
//         cin >> a[i][0] >> a[i][1];
//         a[i][2] = i;
//     }

//     auto solve = [&]() -> void {

//         sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
//             return lhs[0] + lhs[1] < rhs[0] + rhs[1];
//         });

//         cout << "a : " << a << '\n';

//         set<int> ys;
//         for(int i = 0; i < n; i++) ys.insert(a[i][1]);
//         map<int,int> m;
//         int p = 0;
//         for(int x : ys) m[x] = p++;

//         Tree<array<int,2>> tree(p);

//         p = 0;
//         for(int i = 0; i < n; i++) {
//             auto [x, y, id] = a[i];
//             int cur_coord = x + y;
//             while(a[p][0] + a[p][1] + d <= cur_coord) {
//                 tree.update(m[a[p][1]], {a[p][0] + a[p][1], a[p][2]});
//                 p++;
//             }
//             auto [coord, id_q] = tree.query(0, m[y] + 1);
//             cout << "i : " << i << " a[i] : " << a[i] << " query coord : " << coord << " id " << id_q << '\n';
            
//             if(id_q != INT_MAX) {
//                 assert(x + y - coord >= d);
//                 res[id] = tree.f(res[id], {x + y - coord, id_q});
//             }

//         }
//     };

//     auto rotate = [&]() -> void {
//         for(int i = 0; i < n; i++) {
//             swap(a[i][0], a[i][1]);
//             a[i][1] *= -1;
//         }
//     };

//     for(int i = 0; i < 4; i++) {
//         solve();
//         rotate();
//     }

//     for(int i = 0; i < n; i++) cout << (res[i][1] == INT_MAX ? -1 : res[i][1]) << " \n"[i == n - 1];

//     return 0;
// }


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

// //oops misread!

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, d; cin >> n >> d;
//     vector<array<int,2>> one, two, three, four;
//     for(int i = 0; i < n; i++) {
//         int x, y; cin >> x >> y;
//         one.push_back({x + y, i});
//         two.push_back({-(x + y), i});
//         three.push_back({(x - y), i});
//         four.push_back({y - x, i});
//     }

//     vector<array<int,2>> res(n, arra);

//     auto solve = [&](vector<array<int,2>> &a) -> void {
//         sort(a.begin(), a.end());

//         int lo = INT_MAX;
//         int p = 0;
//         for(int i = 0; i < n; i++) {
//             auto [coord, id] = a[i];
//             while(coord - a[p][0] >= d) {
//                 lo = min(lo, a[p][1]);
//                 p++;
//             }
//             res[id] = min(res[id], lo);
//         }

//     };

//     solve(one);
//     solve(two);
//     solve(three);
//     solve(four);
    
//     for(int i = 0; i < n; i++) cout << (res[i] == INT_MAX ? -1 : res[i]) << " \n"[i == n - 1];

//     return 0;
// }
