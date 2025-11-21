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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto solve_cycle = [&](vector<int> a) -> vector<int> {
        if(a.size() == 1) return {};
        if(a.size() == 2) {
            if(a[0] + a[1] < 0) {
                return {0};
            } else {
                return {};
            }
        }

        int n = a.size();

        auto check = [&](int i, int itoggle, int j, int jtoggle) -> bool {
            return a[i] * (itoggle ? -1 : 1) + a[j] * (jtoggle ? -1 : 1) >= 0;
        };

        //fix 2 edges
        for(int first = 0; first < 2; first++) {
            for(int second = 0; second < 2; second++) {
                vector<int> b(n);
                vector<int> res;
                if(first) {
                    b[n-1] ^= 1;
                    b[0] ^= 1;
                    res.push_back(n-1);
                }
                if(second) {
                    b[0] ^= 1;
                    b[1] ^= 1;
                    res.push_back(0);
                }

                vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, 1e9)));
                vector<vector<vector<array<int,3>>>> par(n, vector<vector<array<int,3>>>(2, vector<array<int,3>>(2, {-1,-1,-1})));
                dp[1][b[0]][b[1]] = res.size();
                for(int i = 1; i + 1 < n; i++) {
                    for(int j = 0; j < 2; j++) { //prev prev state
                        for(int k = 0; k < 2; k++) { //prev state
                            for(int l = 0; l < 2; l++) { //should we include the next state
                                //check if it's ok, only check the previous one
                                if(check(i-1, j, i, k ^ l)) { //if it is ok, then check if improved. 
                                    int nxj = k ^ l;
                                    int nxk = l;
                                    int nxval = dp[i][j][k] + l;
                                    if(nxval < dp[i+1][nxj][nxk]) {
                                        dp[i+1][nxj][nxk] = nxval;
                                        par[i+1][nxj][nxk] = {j, k, l};
                                    }
                                }
                            }
                        }
                    }
                }

                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        if(check(n-2, i, n - 1, j ^ b[n-1]) && check(n - 1, j ^ b[n-1], 0, b[0]) && dp[n-1][i][j] <= n / 2) {
                            int ci = i, cj = j;
                            for(int cur = n - 1; cur > 1; cur--) {
                                auto [pj, pk, pl] = par[cur][ci][cj];
                                if(pl) {
                                    res.push_back(cur - 1);
                                }
                                ci = pj;
                                cj = pk;
                            }
                            return res;
                        }
                    }
                }
            }
        }
        assert(0);
    };

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> p(n);
    for(int &x : p) {
        cin >> x;
        x--;
    }

    // cout << "p : " << p << '\n';

    vector<int> vis(n);
    vector<int> res;

    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            int cur = i;
            vector<int> b;
            vector<int> order;
            while(vis[cur] == 0) {
                b.push_back(a[cur]);
                order.push_back(cur);
                vis[cur] = 1;
                cur = p[cur];
            }

            // cout << "b : " << b << '\n';
            // cout << "order : " << order << '\n';

            vector<int> toggles = solve_cycle(b);
            for(int x : toggles) res.push_back(order[x]);
        }
    }

    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) cout << res[i] + 1 << " \n"[i == res.size() - 1];

    return 0;
}
