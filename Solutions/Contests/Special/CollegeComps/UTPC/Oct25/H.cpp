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

    int n, k, m; cin >> n >> k >> m;
    vector<ll> y(n + 1);
    for(int i = 1; i <= n; i++) cin >> y[i];
    y.push_back(m + 1);

    //x, debuff, cost
    vector<vector<array<ll,3>>> a(n + 1);
    for(int i = 0; i < k; i++) {
        int x, y, d; cin >> x >> y >> d;
        a[y].push_back({x, d, LLONG_MAX});
    }
    a[0].push_back({0, 1, 0});
    a.push_back(vector<array<ll,3>>{{0, 1, LLONG_MAX}});

    for(int i = 0; i <= n; i++) {
        ll dy = y[i+1] - y[i];
        sort(a[i+1].begin(), a[i+1].end());
        {
            LineContainer lc;
            int p = 0;
            for(int j = 0; j < a[i+1].size(); j++) {
                while(p < a[i].size() && a[i][p][0] <= a[i+1][j][0]) {
                    auto [x_here, D, cost] = a[i][p];
                    lc.add(D * dy, cost - D * dy * x_here);
                    p++;
                }
                if(lc.size()) {
                    a[i+1][j][2] = min(a[i+1][j][2], lc.query(a[i+1][j][0]));
                    // cout << "1 i : " << i << " j : " << j << '\n';
                }
            }
        }
        {
            LineContainer lc;
            int p = a[i].size() - 1;
            for(int j = a[i+1].size() - 1; j >= 0; j--) {
                while(p >= 0 && a[i][p][0] >= a[i+1][j][0]) {
                    auto [x_here, D, cost] = a[i][p];
                    lc.add(-D * dy, cost + D * dy * x_here);
                    p--;
                }
                if(lc.size()) {
                    a[i+1][j][2] = min(a[i+1][j][2], lc.query(a[i+1][j][0]));
                    // cout << "2 i : " << i << " j : " << j << '\n';
                }
            }
        }
    }

    // for(int i = 0; i <= n + 1; i++) cout << "i : " << i << " a[i] : " << a[i] << '\n';

    cout << a[n+1][0][2] << '\n';

    return 0;
}
