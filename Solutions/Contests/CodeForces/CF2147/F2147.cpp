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
typedef long long ll;
typedef long double ld;
using namespace std;

struct Info {
    int seg_cnt, l, r;
    bool all;
    ll contrib;
    Info(): seg_cnt(0), l(0), r(0), all(0), contrib(0) {}
    Info(int seg_cnt, int l, int r, bool all, ll contrib): seg_cnt(seg_cnt), l(l), r(r), all(all), contrib(contrib) {}
};

ostream& operator<<(ostream& os, Info info) {
    os << "segs : " << info.seg_cnt << " l : " << info.l << " r : " << info.r << " all : " << info.all << " contrib : " << info.contrib;
    return os;
}

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     // for(auto &x : v) os << x << " ";
//     // return os;
//     for(int i = 1; v.size() >= 1 << i; i++) {
//         for(int j = 1 << (i - 1); 1 << i > j; j++) {
//             // os << "i : " << i << " j : " << j << ' ';
//             os << v[j] << ' ';
//         }
//         os << '\n';
//     }
//     return os;
// }

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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll tri(ll x) {
    return x * (x + 1) / 2;
}

template<typename T>
struct Tree {
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n, T def) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    bool isLeaf(int node) {return node >= size;}
    // void update(int pos, T val) { //update 0 indexed, assignment
    //     assert(pos < n && pos >= 0);
    //     int curr = pos + size;
    //     v[curr] = val;
    //     while(curr != 1) {
    //         if(curr & 1) { //handles non-communative operations
    //             v[curr / 2] = f(v[curr ^ 1], v[curr]);
    //         } else {
    //             v[curr / 2] = f(v[curr], v[curr ^ 1]);
    //         }
    //         curr /= 2;
    //     }
    // }

    void update(int l, int r, int delta) {
        // cout << "update edge from " << l << " to " << r << " with delta " << delta << '\n';
        if(r>l) _update(1, 0, size, l, r, delta);
    }
    void _update(int idx, int curl, int curr, int tl, int tr, int delta) {
        // cout << "_update called with idx : " << idx << " curl : " << curl << " curr : " << curr << " tl : " << tl << " tr : " << tr << " delta : " << delta << '\n';
        //no overlap, we are done
        if(curr <= tl || curl >= tr) return;
        //complete overlap, we are also done and we add to delta
        if(tl <= curl && curr <= tr) {
            v[idx].seg_cnt += delta;
        } else {
            int mid = (curl + curr) / 2;
            _update(idx * 2, curl, mid, tl, tr, delta);
            _update(idx * 2 + 1, mid, curr, tl, tr, delta);
        }
        int sz = curr - curl;
        if(isLeaf(idx)) {
            assert(v[idx].seg_cnt >= 0);
            if(v[idx].seg_cnt) {
                v[idx] = Info(v[idx].seg_cnt, 1, 1, 1, tri(sz));
            } else {
                v[idx] = Info(v[idx].seg_cnt, 0, 0, 0, 0);
            }
        } else {
            if(v[idx].seg_cnt) {
                v[idx] = Info(v[idx].seg_cnt, sz, sz, 1, tri(sz));
            } else {
                int lidx = idx * 2, ridx = idx * 2 + 1;
                v[idx].l = (v[lidx].all ? sz / 2 + v[ridx].l : v[lidx].l);
                v[idx].r = (v[ridx].all ? sz / 2 + v[lidx].r : v[ridx].r);
                v[idx].all = v[lidx].all && v[ridx].all;
                v[idx].contrib = v[lidx].contrib + v[ridx].contrib - (tri(v[lidx].r) + tri(v[ridx].l)) + tri(v[lidx].r + v[ridx].l);
            }
        }
    }
    // T at(int idx) {
    //     assert(idx >= 0 && idx < n);
    //     return v[idx + size];
    // }
    // T query(int l, int r) {//queries in range [l,r)
    //     return _query(1,0,size,l,r);
    // }
    // T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
    //     if(currr <= targetl || currl >= targetr) return base;
    //     if(currl >= targetl && currr <= targetr) return v[idx];
    //     int mid = (currl + currr) / 2;
    //     return f(
    //         _query(idx * 2, currl, mid, targetl, targetr),
    //         _query(idx * 2 + 1, mid, currr, targetl, targetr)
    //     );
    // }
    ll query() {
        return v[1].contrib;
    }
};

void solve(int n, int q, vector<int> a, vector<int> b, vector<array<int,3>> queries, int debug = false) {

    if(debug) {
        cout << n << " " << q << endl;
        for(int i = 0; i < n; i++) cout << a[i] + 1 << " \n"[i == n - 1];
        for(int i = 0; i < n; i++) cout << b[i] + 1 << " \n"[i == n - 1];
        for(int i = 0; i < q; i++) for(int j = 0; j < 3; j++) cout << queries[i][j] + 1 << " \n"[j == 2];
    }
    
    vector<int> ra(n),rb(n);
    Tree<Info> tree(n - 1, Info());


    for(int i = 0; i < n; i++) ra[a[i]] = i;
    for(int i = 0; i < n; i++) rb[b[i]] = i;

    set<array<int,2>> active_segs;

    auto _upd = [&](int l, int r, int delta) -> void {
        if(delta == 1) {
            assert(active_segs.count({l, r}) == 0);
            active_segs.insert({l, r});
        } else {
            assert(active_segs.count({l, r}));
            active_segs.erase({l, r});
        }
        tree.update(l, r, delta);
    };  

    for(int i = n - 1; i > 0; i--) {
        //looking at item where person b values it at i. 
        int b_item = rb[i];
        int nx_item = rb[i-1];
        //b will trade item b_item for nx_item
        int b_idx = a[b_item];
        int nx_idx = a[nx_item];

        //b will trade 
        _upd(b_idx, nx_idx, 1);
    }

    // cout << "n zzzz : " << n << '\n';
    // cout << "a : " << a << "\n";
    // cout << "ra : " << ra << '\n';
    // cout << "b : " << b << '\n';
    // cout << "rb : " << rb << '\n';

    // cout << "debug starting contrib : " << tree.query() << '\n';
    // cout << "root info : " << tree.v[1] << '\n';

    auto upd = [&](int l, int r, int delta, set<array<int,2>> &vis) -> void {
        if(vis.count({l,r}) == 0) {
            _upd(l, r, delta);
            vis.insert({l, r});
        }
    };

    //apply delta to all current edges into and a[idx]. 
    auto upd_segs = [&](int item, int delta, set<array<int,2>> &vis) {
        //update segments that involve the item with value idx. 
        int idx = a[item];
        int b_val = b[item];

        if(b_val) {
            int lower_val_idx = a[rb[b_val - 1]];
            upd(idx, lower_val_idx, delta, vis);
        }
        if(b_val + 1 < n) {
            int higher_val_idx = a[rb[b_val + 1]];
            upd(higher_val_idx, idx, delta, vis);
        }
    };

    for(int qq = 0; qq < q; qq++) {
        // cout << "segs before chaos : " << active_segs << '\n';
        auto [tp, i, j] = queries[qq];
        set<array<int,2>> vis;
        if(tp == 0) { //updating a
            upd_segs(i, -1, vis);
            upd_segs(j, -1, vis);

            swap(a[i], a[j]);
            ra[a[i]] = i;
            ra[a[j]] = j;

            vis.clear();
            upd_segs(i, 1, vis);
            upd_segs(j, 1, vis);
        } else {
            upd_segs(i, -1, vis);
            upd_segs(j, -1, vis);

            swap(b[i], b[j]);
            rb[b[i]] = i;
            rb[b[j]] = j;

            vis.clear();
            upd_segs(i, 1, vis);
            upd_segs(j, 1, vis);
        }

        // cout << "a : " << a << "\n";
        // cout << "b : " << b << "\n";

        cout << tri(n) + tree.query() << '\n';

    }

    // cout << "segs after chaos : " << active_segs << '\n';

}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    for(int &x : a) {
        cin >> x;
        x--;    
    }
    for(int &x : b) {
        cin >> x;
        x--;
    }
    vector<array<int,3>> queries(q);
    for(auto &x : queries) {
        for(auto &y : x) {
            cin >> y;
            y--;
        }
    }

    solve(n, q, a, b, queries);
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void tcg(int n, int q) {
    vector<int> a(n), b(n);
    iota(a.begin(), a.end(), 0);
    iota(b.begin(), b.end(), 0);
    shuffle(a.begin(), a.end(), rng);
    shuffle(b.begin(), b.end(), rng);

    vector<array<int,3>> queries(q);
    for(int i = 0; i < q; i++) {
        queries[i][0] = rng() % 2;
        queries[i][1] = rng() % n;
        queries[i][2] = rng() % n;
        while(queries[i][1] == queries[i][2]) queries[i][2] = rng() % n;
    }
    solve(n, q, a, b, queries, 0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    // for(int i = 0; i < 1000; i++) {
    //     tcg(5, 5);
    // }

    return 0;
}