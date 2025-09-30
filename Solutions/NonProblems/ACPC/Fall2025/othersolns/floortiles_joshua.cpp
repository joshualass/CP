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

bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa, vector<int>& A, vector<int>& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(A.begin(), A.end(), 0);
		fill(B.begin(), B.end(), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
        for(int i = 0; i < g.size(); i++) {
            if(A[i] == 0) {
                cur.push_back(i);
            }
        }
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		// rep(a,0,sz(g))
		// 	res += dfs(a, 0, g, btoa, A, B);
        for(int i = 0; i < g.size(); i++) {
            res += dfs(i, 0, g, btoa, A, B);
        }
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<vector<int>> id(n, vector<int>(m));
    array<int,2> p = {};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.') {
                int h = (i + j) % 2;
                id[i][j] = p[h]++;
            }
        }
    }

    vector<vector<int>> g(p[0]);
    vector<int> btoa(p[1], -1);

    vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if((i + j) % 2 == 0 && a[i][j] == '.') {
                for(int t = 0; t < 4; t++) {
                    int ni = i + dx[t];
                    int nj = j + dy[t];
                    if(ni >= 0 && ni < n && nj >= 0 && nj < m && a[ni][nj] == '.') {
                        // cout << "add edge from (" << i << ", " << j << ") to (" << ni << ", " << nj << ")\n";
                        g[id[i][j]].push_back(id[ni][nj]);
                    }
                }
            }
        }
    }

    // cout << "id\n" << id << '\n';
    // cout << "g\n" << g << '\n';

    int bc = 0;
    for(int i = 0; i < n; i++) bc += count(a[i].begin(), a[i].end(), '.');

    int flow = hopcroftKarp(g, btoa);

    // cout << "bc : " << bc << '\n';
    // cout << "flow : " << flow << '\n';

    cout << (flow == bc / 2 ? "YES" : "NO") << '\n';

    return 0;
}
