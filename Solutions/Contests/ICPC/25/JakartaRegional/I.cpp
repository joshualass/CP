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

template<typename T>
struct Segtree {
    int n;
    T* t;
    T uneut, qneut;
    function<T(T, T)> fmodify, fcombine;

    Segtree() {}
    Segtree(int n, T updateNeutral, T queryNeutral, function<T(T, T)> fm, function<T(T, T)> fc) {
        this->n = n;
        t = new T[2 * n];
        this->fmodify = fm;
        this->fcombine = fc;
        uneut = updateNeutral;
        qneut = queryNeutral;
        for(int i = 0; i < n; i++) t[i + n] = uneut;
        build();
    }

    void build() {
        for(int i = n - 1; i > 0; i--) {
            t[i] = fcombine(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int p, T value) {
        p += n;
        t[p] = fmodify(t[p], value);
        for(p /= 2; p > 0; p /= 2) {
            t[p] = fcombine(t[p * 2], t[p * 2 + 1]);
        }
    }

    T query(int l, int r) {
        if(l >= r) return qneut;
        T l_res = qneut, r_res = qneut;
        bool l_none = true, r_none = true;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(l_none) {l_none = false; l_res = t[l];}
                else l_res = fcombine(l_res, t[l]);
                l ++;
            }
            if(r % 2 == 1) {
                r --;
                if(r_none) {r_none = false; r_res = t[r];}
                else r_res = fcombine(t[r], r_res);
            }
        }
        if(l_none) return r_res;
        if(r_none) return l_res;
        return fcombine(l_res, r_res);
    }

    T query(int ind) {
        return this->query(ind, ind + 1);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    function<int(int, int)> fmodify = [](const int src, const int val) -> int {return val;};
    function<int(int, int)> fcombine = [](const int a, const int b) -> int {return max(a, b);};

    int n; cin >> n;
    vector<string> a(3);
    for(auto &x : a) cin >> x;

    auto is_clear = [&](int idx, array<int,3> bm) -> int {
        for(int i = 0; i < 3; i++) {
            if(bm[i] && a[i][idx] == '#') return 0;
        }
        return 1;
    };

    //precompute i prefix and suffix
    vector<int> p(n, -1e8), s(n, -1e8);
    {
        int cur = 0, best = -1e8;
        for(int i = 0; i < n; i++) {
            if(is_clear(i, {1,1,1})) {
                cur++;
            } else {
                cur = 0;
            }
            if(cur) best = max(best, cur);
            // cout << "i : " << i << " best : " << best << '\n';
            p[i] = best;
        }
    }

    {
        int cur = 0, best = -1e8;
        for(int i = n - 1; i >= 0; i--) {
            if(is_clear(i, {1,1,1})) {
                cur++;
            } else {
                cur = 0;
            }
            if(cur) best = max(best, cur);
            s[i] = best;
        }
    }

    // cout << "p\n";
    // for(int x : p) cout << x << " ";
    // cout << '\n';
        
    auto gpi = [&](int idx) -> int {
        if(idx >= 0) return p[idx];
        return -1e8;
    };
    
    auto gsi = [&](int idx) -> int {
        if(idx < n) return s[idx];
        return -1e8;
    };

    Segtree<int> segt(n, -1e8, -1e8, fmodify, fcombine);

    //compute the seg values
    for(int i = 0; i < n; i++) {
        if(is_clear(i, {1,1,1})) {
            int val = 4 + gpi(i - 2) - 2 * i;
            // cout << "update i : " << i << " val : " << val << '\n';
            segt.modify(i, 4 + gpi(i - 2) * 3 - 2 * i);
        }
    }

    int res = -1e8;

    //check and update our answer for putting an o with endpoints at l and r
    auto test = [&](int l, int r) -> void {
        // cout << "test called l : " << l << " r : " << r << '\n';
        if(l + 2 > r) return; //not large enough
        int q = r - l + 1;
        int i_len = min(q, gpi(l - 2) + gsi(r + 2));
        if(i_len > 0) {
            res = max(res, i_len * 3 + q * 2 + 2);
        }
    };

    int left_ok = 1e8;
    vector<int> pos;
    for(int i = 0; i < n; i++) {
        if(is_clear(i, {1,1,1})) {
            //binary search the latest index such that if we make this index the left endpoint of the O, we will not have to consider 
            // the restriction at all. 
            if(pos.size()) {
                int l = -1, r = pos.size() - 1;
                while(r >= 0 && pos[r] + 2 > i) r--;
                while(l != r) {
                    // cout << "l : " << l << " r : " << r << '\n';
                    int m = (l + r + 1) / 2;
                    int q = i - pos[m] + 1;
                    int z = gpi(pos[m] - 2);
                    int zz = gsi(i + 2);
                    // cout << "m : " << m << '\n';
                    if(q >= z + zz) {
                        l = m;
                    } else {
                        r = m - 1;
                    }
                }

                // cout << "i : " << i << " l : " << l << " pos[l] : " << pos[l] << '\n';
                if(l + 1 < pos.size()) test(pos[l+1], i);

                if(l != -1) {

                    // cout << "left_ok : " << left_ok << '\n';
                    int qval = segt.query(left_ok, pos[l] + 1);
                    int test = qval + i * 2 + gsi(i + 2) * 3;
                    // cout << "i : " << i << " qval : " << qval << " test : " << test << '\n';
                    res = max(res, test);

                }
            }
            pos.push_back(i);
            left_ok = min(left_ok, i);
        } else if(!is_clear(i, {1,0,1})) {
            left_ok = 1e8;
            pos.clear();
        }
    }

    cout << (res < 0 ? -1 : res) << '\n';

    return 0;
}
