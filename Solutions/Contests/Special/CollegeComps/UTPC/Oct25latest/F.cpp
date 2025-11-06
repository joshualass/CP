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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

set<pii>::iterator addInterval(set<pii>& is, int L, int R) {
	if (L == R) return is.end();
	auto it = is.lower_bound({L, R}), before = it;
	while (it != is.end() && it->first <= R) {
		R = max(R, it->second);
		before = it = is.erase(it);
	}
	if (it != is.begin() && (--it)->second >= L) {
		L = min(L, it->first);
		R = max(R, it->second);
		is.erase(it);
	}
	return is.insert(before, {L,R});
}

void removeInterval(set<pii>& is, int L, int R) {
	if (L == R) return;
	auto it = addInterval(is, L, R);
	auto r2 = it->second;
	if (it->first == L) is.erase(it);
	else (int&)it->second = L;
	if (R != r2) is.emplace(R, r2);
}

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dsubuild();

    int n; cin >> n;
    map<int,set<pair<int,int>>> rows, cols;
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if(x1 == y1 && x2 == y2) continue;
        if(x1 == x2) {
            addInterval(cols[x1], min(y1, y2), max(y1,y2) + 1);
        } else {
            addInterval(rows[y1], min(x1, x2), max(x1,x2) + 1);
        }
    }

    int p = 0;
    map<array<int,3>, int> rm, cm;
    for(auto [x, pts] : cols) {
        for(auto [l, r] : pts) {
            cm[{x, l, r}] = p++;
        }
    }

    for(auto [y, pts] : rows) {
        for(auto [l, r] : pts) {
            rm[{y, l, r}] = p++;
        }
    }

    int f = 0;
    for(auto [x, col_pts] : cols) {
        for(auto [coll, colr] : col_pts) {
            int col_id = cm[{x, coll, colr}];
            for(auto [y, row_pts] : rows) {
                for(auto [rowl, rowr] : row_pts) {
                    int row_id = rm[{y, rowl, rowr}];
                    if(rowl <= x && x < rowr && coll <= y && y < colr) {
                        if(find(col_id) != find(row_id)) {
                            merge(col_id, row_id);
                        } else {
                            f = 1;
                        }
                    }
                }
            }
        }
    }

    cout << (f ? "YES" : "NO") << '\n';

    return 0;
}
