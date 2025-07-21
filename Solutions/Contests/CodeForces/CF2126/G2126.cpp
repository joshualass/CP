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

/*
1
4
4 2 3 1

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

struct Info {
    int l, r, all, res;
    Info(): l(0), r(0), all(0), res(0) {}
    Info(int l, int r, int all, int res): l(l), r(r), all(all), res(res) {}
};

Info operator+(Info lhs, Info rhs) {

    Info res;
    res.l = max(lhs.l, lhs.all + rhs.l);
    res.r = max(rhs.r, rhs.all + lhs.r);
    res.all = lhs.all + rhs.all;
    res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});

    return res;

}

Info base(0, 0, 0, 0);

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
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) { //queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    vector<vector<int>> b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        b[a[i]].push_back(i);
    }    

    int res = 0;
    set<int> s;
    Tree<Info> tree(n, Info(0, 0, -1, 0));

    for(int i = 0; i < n; i++) {
        s.insert(i);
        tree.update(i, Info(0, 0, -1, 0));
    }

    int lo = INT_MAX;

    for(int i = n - 1; i >= 0; i--) {
        lo = min(lo, i);

        for(int idx : b[i]) {
            s.erase(idx);
            tree.update(idx, Info(1, 1, 1, 1));
            while(s.upper_bound(idx) != s.end()) {
                int nx = *s.upper_bound(idx);
                Info res = tree.query(0, nx);
                // cout << "i : " << i << " idx : " << idx << " nx : " << nx << " res.r : " << res.r << '\n';
                if(res.r > 0) {
                    lo = min(lo, a[nx]);
                    s.erase(nx);
                } else {
                    break;
                }
            }
            while(s.lower_bound(idx) != s.begin()) {
                int nx = *--s.lower_bound(idx);
                Info res = tree.query(nx + 1, n);
                if(res.l > 0) {
                    lo = min(lo, a[nx]);
                    s.erase(nx);
                } else {
                    break;
                }
            }
        }

        // cout << "i : " << i << '\n';
        // cout << "s : " << s << '\n';
        // cout << "lo : " << lo << '\n';

        res = max(res, i - lo);

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}