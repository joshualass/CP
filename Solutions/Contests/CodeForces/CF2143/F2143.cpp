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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int d = 20;
struct B {

    int sz = 0;
    array<int,d> basis = {};
    B(): basis({}) {}

    B& operator=(const B& other) {
        this->basis = other.basis;
        return *this;
    }

    B operator+(const B& other) const {
        B res;
        res.basis = this->basis;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(other.basis[bit]) res.insert(other.basis[bit]);
        }
        return res;
    }

    bool insert(int x) { //returns true if insert was successful
        // cout << "insert x : " << x << '\n';
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    sz++;
                    basis[bit] = x;
                    return 1;
                }
            }
        }
        return 0;
    }

    bool find(int x) { //return 0/1 if element is in the basis, does not insert. 
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    return 0;
                }
            }
        }
        return 1;
    }

    int query() {
        int res = 0;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((res >> bit) & 1) == 0) res ^= basis[bit];
        }
        return res;
    }

    int order(int x) { //finds the order that x has in the basis. 
        //check that x is in this basis
        assert(find(x));
        int res = 0, idx = sz - 1;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(basis[bit]) {
                if((x >> bit) & 1) {
                    res += 1 << idx;
                }
                idx--;
            }
        }
        return res;
    }

    int get(int order) { //given order, find the value in this basis. 
        assert(order < (1 << sz));
        int res = 0, idx = sz - 1;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(basis[bit]) {
                if(((order >> idx) & 1) != ((res >> bit) & 1)) {
                    res ^= basis[bit];
                }
                idx--;
            }
        }
        return res;
    }

};

void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<B> b(n);
    vector<vector<int>> bci(n);
    for(int i = 0; i < n; i++) {
        for(int j = i; j >= 0; j--) {
            if(b[j].insert(a[i])) {
                bci[j].push_back(i);
            } else {
                break;
            }
        }
    }

    vector<int> pc(n);
    for(int i = 0; i < n; i++) {
        int r = i;
        B cur;
        bci[i].push_back(1e9);
        int prev_val = -1;
        for(int j = 0; j < bci[i].size(); j++) {
            int idx = bci[i][j];
            if(j) {
                int prev_idx = bci[i][j-1];
                int prev_ord = cur.order(prev_val);
                int before_ord = prev_ord + ((idx - 1) - prev_idx);
                //we can make up to this minimum element previously. 
                if(before_ord < (1 << cur.sz)) {
                    int before_val = cur.get(before_ord);
                    cur.insert(a[idx]);
                    int new_ord = cur.order(before_val);
                    //we cannot make the next element
                    if(new_ord + 1 == (1 << cur.sz)) {
                        r = idx - 1;
                        break;
                    }
                    prev_val = cur.get(new_ord + 1);
                    // cout << "i : " << i << " j : " << j << " idx : " << idx << " prev_val : " << prev_val << '\n';
                } else {
                    int mx_ord = (1 << cur.sz) - 1;
                    r = prev_idx + (mx_ord - prev_ord);
                    break;
                }
                
            } else {
                cur.insert(a[idx]);
                prev_val = 0;
            }
        }
        pc[i] = r;
    }

    // cout << "pc : " << pc << '\n';

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        cout << (r <= pc[l] ? "YES" : "NO") << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}