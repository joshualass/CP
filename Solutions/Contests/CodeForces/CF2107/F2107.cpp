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
idea took a while to come about. here was the thought process

saw the n^2 dp trick. 

then, tried to solve the problem by inserting the smallest elements at a time. 
this doesn't quite work bc it's still quite hard to compute. 

the problem shows that it's possible to solve each prefix, so we should try to solve each prefix and 
have some insert operation that works. 

The first thing we can see is that we do want to do some CHT tricks where when we solve for each answer. 
If the answer for the prefix at index i is x, then we can guarantee that we can do x + 2 for each extra index
by doing 2 swaps and using x. 

the next problem is how much do we want to use this element. 

It is always optimal to use this element until we encounter an element that is <= . At that point we will use that element. 

we take the minimum from using this element as much as possible until a <= is encountered or the cost 
from bringing an element here. 
*/

//currently setup for max queries
//y = kx + m
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
        k *= -1;
        m *= -1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return -(l.k * x + l.m);
	}
};

void solve() {
    
    int n; cin >> n;
    LineContainer lc;

    vector<ll> a(n);
    map<int,int> m;

    auto add_map = [&](int val, int idx) -> void {
        m[val] = idx;
        while(1) {
            auto it = m.upper_bound(val);
            if(it != m.end()) {
                m.erase(it);
            } else {
                break;
            }
        }
    };

    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        ll res = 1e18;

        if(i == 0) {
            res = x;
        } else {
            auto it = m.upper_bound(x);
            if(it != m.begin()) {
                it--;
                int idx = it->second;
                res = a[idx] + x + (x + 1) * (i - idx - 1);
            } else {
                res = x + (x + 1) * i;
            }
            res = min(res, lc.query(i));
        }
        a[i] = res;
        lc.add((x + 2), -(x + 2) * i + res);
        add_map(x, i);
        // cout << res << " \n"[i == n - 1];
    }
    cout << a.back() << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}