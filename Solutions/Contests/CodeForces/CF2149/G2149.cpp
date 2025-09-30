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
had to optimize memory, it seems like randomization could help a lot here like fishy did. 
i did a segtree - style where i chop the interval into segs and a element can be a third majority if it is 
a majority in one of the segs, then, we consider logn * k elements per query, building O(n logn * k) on the segs
but need to optimize for memory. 
*/

struct Info {
    map<int,int> m;
    set<int> s;
    int sz = 0, len = 0;
    Info() {}
    void insert(int x) {
        sz++;
        m[x]++;
        if(m[x] > (sz / 3)) s.insert(x);
        for(auto it = s.begin(); it != s.end();) {
            int val = *it;
            if(!(m[val] > (sz / 3))) {
                it = s.erase(it);
            } else {
                it++;
            }
        }
    }
};

struct Tree {
    vector<set<int>> v;
    int n, size;
    // Tree(int n, Info def) {
    //     this->n = n; //max number of elements
    //     size = 1;
    //     while(size < n) size *= 2;
    //     v.assign(size * 2, def);

    // }
    // void update(int pos, int x) { //update 0 indexed, assignment
    //     assert(pos < n && pos >= 0);
    //     int curr = pos + size;
    //     v[curr].insert(x);
    //     while(curr != 1) {
    //         curr /= 2;
    //         v[curr].insert(x);
    //     }
    // }
    Tree(vector<int> a) {
        this->n = a.size();
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {});
        build(1, 0, size, 0, n, a);
    }
    void build(int idx, int curl, int curr, int tl, int tr, vector<int> &a) {
        if(curr <= tl || curl >= tr) return;
        if(curl >= tl && curr <= tr) {
            map<int,int> m;
            for(int i = curl; i < curr; i++) m[a[i]]++;
            int sz = curr - curl;
            for(auto [k, fre] : m) {
                if(fre > sz / 3) v[idx].insert(k);
            }
        }
        if(curl + 1 == curr) return;
        int mid = (curl + curr) / 2;
        build(idx * 2, curl, mid, tl, tr, a);
        build(idx * 2 + 1, mid, curr, tl, tr, a);
    }
    set<int> query(int l, int r) {//queries in range [l,r)
        set<int> res;
        _query(1,0,size,l,r, res);
        return res;
    }
    void _query(int idx, int currl, int currr, int &targetl, int &targetr, set<int> &res) {
        if(currr <= targetl || currl >= targetr) return;
        if(currl >= targetl && currr <= targetr) {
            for(int x : v[idx]) res.insert(x);
            return;
        }
        int mid = (currl + currr) / 2;
        _query(idx * 2, currl, mid, targetl, targetr, res);
        _query(idx * 2 + 1, mid, currr, targetl, targetr, res);
    }
};

void solve() {
    
    int n, q; cin >> n >> q;

    map<int, map<int,int>> m;
    vector<int> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        int x = a[i];
        int freq = 0;
        if(m[x].size()) {
            freq = (--m[x].end())->second;
        }
        m[x][i] = freq + 1;
    }

    Tree tree(a);

    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        l--;
        set<int> cs = tree.query(l, r);
        set<int> ok;
        for(int c : cs) {
            int first, last;
            if(m[c].lower_bound(r) != m[c].begin()) {
                last = (--m[c].lower_bound(r))->second;
            } else {
                last = 0;
            }
            if(m[c].lower_bound(l) != m[c].begin()) {
                first = (--m[c].lower_bound(l))->second;
            } else {
                first = 0;
            }
            if(last - first > (r - l) / 3) ok.insert(c);
        }
        if(ok.empty()) {
            cout << "-1\n";
        } else {
            for(int x : ok) cout << x << " ";
            cout << '\n';
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}