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

    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);    //  {x, weight}
    for(int i = 0; i < n; i++) {
        int w;
        cin >> w;
        a[i] = {i, w};
    }
    a.push_back({0, -1});
    n ++;
    sort(a.begin(), a.end());
    int B = 28;
    vector<vector<int>> indmp(n, vector<int>(B, -1));
    vector<vector<bool>> seeyou(n, vector<bool>(B, 0));
    int indptr = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < B; j++) indmp[i][j] = indptr ++;
    }
    vector<vector<int>> c(indptr);
    for(int i = 0; i < n; i++) seeyou[i][0] = true;
    for(int i = 1; i < B; i++) {
        int width = (1 << i);
        int lptr = 0, rptr = 0;
        //currently contain all elements in range [lptr, rptr)
        set<pair<int, int>> s;  //{weight, ind};
        for(int j = 0; j < n; j++) {
            int l = a[i].first - width / 2;
            int r = a[i].first + width / 2 + 1;
            while(rptr != n && a[rptr].first < r) {
                s.insert({a[rptr].second, rptr});
                rptr ++;
            }
            while(lptr != n && a[lptr].first < l) {
                s.erase({a[lptr].second, lptr});
                lptr ++;
            }
            auto ptr = s.rbegin();
            for(int ii = 0; ii < min((int) s.size(), k); ii++) {
                int ind = ptr->second;
                ptr ++;
                c[indmp[j][i]].push_back(indmp[ind][i]);
                if(ind == j) seeyou[j][i] = true;
            }
            if(i != B - 1) c[indmp[j][i]].push_back(indmp[j][i + 1]);
            if(i != 0) c[indmp[j][i]].push_back(indmp[j][i - 1]);
        }   
    }
    vector<int> d(indptr, 1e9);
    int sind = -1;
    for(int i = 0; i < n; i++) {
        if(a[i].first == 0) sind = indmp[i][1];
    }
    assert(sind != -1);
    d[sind] = 0;
    queue<int> q;
    q.push(sind);
    while(q.size() != 0) {
        int cur = q.front();
        q.pop();
        for(int x : c[cur]) {
            if(d[x] == 1e9) {
                d[x] = d[cur] + 1;
                q.push(x);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(a[i].first == 0) continue;
        for(int j = 0; j < B; j++) {
            
        }
    }

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

// struct Tree {
//     vector<array<int,4>> a;
//     int sz;

//     Tree(int n) {
//         sz = 1;
//         while(sz <= n) sz *= 2;
//         a.assign(sz * 2, array<int,4>{-1,-1,-1,-1});
//     }

//     array<int,4> f(array<int,4> lhs, array<int,4> rhs) {
//         array<int,4> res = {};
//         int lp = 0, rp = 0;
//         for(int i = 0; i < 4; i++) {
//             if(lhs[lp] > rhs[rp]) {
//                 res[i] = lhs[lp++];
//             } else {
//                 res[i] = rhs[rp++];
//             }
//         }
//         return res;
//     }

//     void update(int idx, array<int,4> val) {
//         // cout << "update called with idx : " << idx << " val : " << val[0] << '\n';
//         int cur = idx + sz;
//         a[cur] = val;
//         while(cur != 1) {
//             a[cur / 2] = f(a[cur], a[cur ^ 1]);
//             cur /= 2;
//         }
//     }

//     array<int,4> query(int l, int r) {
//         return _query(1, 0, sz, l, r);
//     }

//     array<int,4> _query(int idx, int cl, int cr, int tl, int tr) {
//         // cout << "_query called with idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << '\n';
//         if(cr <= tl || cl >= tr) return {-1,-1,-1,-1};
//         if(tl <= cl && cr <= tr) return a[idx];
//         int mid = (cl + cr) / 2;
//         return f(
//             _query(idx * 2, cl, mid, tl, tr),
//             _query(idx * 2 + 1, mid, cr, tl, tr)
//         );
//     }
// };

// /*
// 4 2
// 100
// 4
// 1
// 3

// 4 1
// 1
// 2
// 3
// 4

// */

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, k; cin >> n >> k;
//     vector<vector<int>> vis(n + 1, vector<int>(29, -1));
//     vector<int> a(n + 1); //a[i] => the position of point with weight i
//     vector<array<int,2>> b(n + 1); //b[i] => {coordinate, weight}

//     for(int i = 1; i < n + 1; i++) {
//         int x; cin >> x;
//         a[i] = x;
//         b[i] = {x, i};
//     }

//     sort(b.begin(), b.end());

//     // for(int i = 0; i < n + 1; i++) {
//     //     cout << "i : " << i << " b[i] : ";
//     //     for(int j = 0; j < 2; j++) cout << b[i][j] << " ";
//     //     cout << '\n';
//     // }

//     Tree tree(n + 1);
//     for(int i = 0; i < n + 1; i++) {
//         tree.update(i, {b[i][1], -1, -1, -1});
//     }

//     // for(int i = 0; i < tree.a.size(); i++) {
//     //     cout << "i : " << i << " tree[i] : ";
//     //     for(int j = 0; j < 4; j++) cout << tree.a[i][j] << " ";
//     //     cout << '\n';
//     // }

//     queue<array<int,3>> q; // {weight, interval width, step}
//     auto add_q = [&](int i, int x, int s) -> void {
//         if(vis[i][x] != -1) return;
//         vis[i][x] = s;
//         q.push({i, x, s});
//     };

//     add_q(0, 0, 0);

//     while(q.size()) {
//         auto [w, x, s] = q.front();
//         q.pop();

//         // cout << "w : " << w << " x : " << x << " s : " << s << '\n';

//         //try zooming in
//         if(x) add_q(w, x - 1, s + 1);
//         //try zooming out 
//         if(x + 1 < 29) add_q(w, x + 1, s + 1);

//         int pos = a[w];

//         //try the highest k elements
//         int lo = lower_bound(b.begin(), b.end(), array<int,2>{pos - (1 << x), -1}) - b.begin();
//         int hi = lower_bound(b.begin(), b.end(), array<int,2>{pos + (1 << x) + 1, -1}) - b.begin();
//         // cout << "lo : " << lo << " hi : " << hi << '\n';
//         array<int,4> arr = tree.query(lo, hi);
//         // cout << "arr\n";
//         // for(int i = 0; i < 4; i++) cout << arr[i] << " ";
//         // cout << '\n';
//         for(int i = 0; i < k; i++) {
//             if(arr[i] != -1) add_q(arr[i], x, s + 1);
//         }
//     }

//     for(int i = 1; i <= n; i++) {
//         int res = INT_MAX;
//         for(int j = 0; j < 29; j++) {
//             int pos = a[i];
//             int lo = lower_bound(b.begin(), b.end(), array<int,2>{pos - (1 << j), -1}) - b.begin();
//             int hi = lower_bound(b.begin(), b.end(), array<int,2>{pos + (1 << j) + 1, -1}) - b.begin();
//             array<int,4> arr = tree.query(lo, hi);
//             int f = 0;
//             for(int l = 0; l < 4; l++) if(arr[l] == i) f = 1;
//             if(f) {
//                 res = min(res, vis[i][j]);
//             }
//         }
//         if(vis[i][0] != -1) res = min(res, vis[i][0] + 1);
//         cout << (res == INT_MAX ? -1 : res) << '\n';
//     }

//     return 0;
// }
