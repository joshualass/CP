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
tcg is op

5
1 2 4 1 3 
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int debug = 0;
int n; 
vector<int> a;
int result_fast, result_slow;

void solve() {

    if(!debug) {
        cin >> n;
        a.assign(n, 0);
        for(int &x : a) cin >> x;
    }

    auto check = [&](int m) -> int {

        // cout << "m : " << m << '\n';
        //we are seeing if it's always possible to make this max m. 
        vector<vector<int>> adj(n);
        int ms = -1;
        set<array<int,2>> s; // {val, idx to get val}

        for(int i = 0; i < n; i++) {
            int leq = a[i] - m;
            auto it = s.begin();
            while(it != s.end() && (*it)[0] <= leq) {
                adj[i].push_back((*it)[1]);
                it++;
            }
            if(adj[i].size() >= 3) {
                if(ms == -1 || ms == i) {
                    ms = i;
                } else {
                    return 1;
                }
            }
            s.insert({a[i], i});
        }

        // cout << "there are not 2 left bigs\n";

        s.clear();
        for(int i = n - 1; i >= 0; i--) {
            int geq = a[i] + m;
            auto it = s.lower_bound({geq, -1});
            while(it != s.end()) {
                adj[i].push_back((*it)[1]);
                it++;
            }
            if(adj[i].size() >= 3) {
                if(ms == -1 || ms == i) {
                    ms = i;
                } else {
                    return 1;
                }
            }
            s.insert({a[i], i});
        }

        // cout << "there are not 2 left + right bigs\n";
        //if we make it here, everything has degree <= 2, except for possibly a big node. 
        
        if(ms == -1) {
            int mx_sz = 0;
            for(int i = 0; i < n; i++) mx_sz = max(mx_sz, (int) adj[i].size());
            if(mx_sz <= 1) return 0;
            vector<int> cand;
            for(int i = 0; i < n; i++) {
                if(adj[i].size() >= 2) {
                    cand.push_back(i);
                } 
            }
            if(cand.size() >= 5) {
                return 1;
            }
            // cout << "cands : " << cand << '\n';
            for(int start : cand) {
                int gc = 0;
                int counter_found = 0;
                for(int i = 0; i < n; i++) {
                    if(i != start) {
                        int cnt = 0;
                        for(int to : adj[i]) {
                            if(to != start) {
                                cnt++;
                            }
                        }
                        if(cnt >= 2) {
                            // cout << "first player has to box this idx : " << start << endl;    
                            counter_found = 1;
                        }
                        // if(cnt <= 1) {
                        //     return 0;
                        // }
                    }
                }
                if(!counter_found) return 0;
            }
            // cout << "gc : " << gc << endl;
            // return gc >= 2;
            return 1;
            // return gc != cand.size();
        } else {
            //we must start on must start. 
            for(int i = 0; i < n; i++) {
                if(i != ms) {
                    int cnt = 0;
                    for(int to : adj[i]) {
                        if(to != ms) {
                            cnt++;
                        }
                    }
                    if(cnt >= 2) {
                        // cout << "must start is good, i will play at index i : " << i << endl;    
                        return 1;
                    }
                }
            }
            return 0;
        }
    };

    int l = -1e9, r = 1e9;
    while(l != r) {
        int m = (l + r + 1) / 2;
        if(check(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    
    if(!debug) {
        cout << l << '\n';
    }
    result_fast = l;

}

void solve_slow() {

    map<array<vector<int>, 2>, int> dp;

    auto dfs = [&](auto self, vector<int> a, vector<int> locked, int turn) -> int {
        if(dp.count({a, locked}) == 0) {
            vector<int> moves;
            for(int i = 0; i < a.size(); i++) {
                if(locked[i] == 0) {
                    moves.push_back(i);
                }
            }
            // cout << "a : " << a << '\n';
            // cout << "l : " << locked << '\n';
            // cout << "moves : " << moves << '\n';

            if(moves.size() == 0) {
                int score = INT_MIN;
                for(int i = 0; i < a.size(); i++) {
                    for(int j = i + 1; j < a.size(); j++) {
                        score = max(score, a[j] - a[i]);
                    }
                }
                // cout << "ttfang a : " << a << '\n';
                // cout << "score ... : " << score << '\n';
                dp[{a, locked}] = score;
            } else {
                int score;
                if(turn == 0) {
                    score = INT_MAX;
                    for(int move : moves) { 
                        vector<int> ac = a, lc = locked;
                        ac.erase(ac.begin() + move);
                        lc.erase(lc.begin() + move);
                        score = min(score, self(self, ac, lc, turn ^ 1));
                    }
                    // cout << "maxing\n";
                } else {
                    score = INT_MIN;
                    for(int move : moves) {
                        vector<int> ac = a, lc = locked;
                        lc[move] = 1;
                        int val = self(self, ac, lc, turn ^ 1);
                        // cout << "move : " << move << " val : " << val << '\n';
                        score = max(score, val);
                    }
                    // cout << "mining\n";
                }
                // cout << "score from try everything : " << score << '\n';
                dp[{a, locked}] = score;
            }
            // cout << "a : " << a << '\n';
            // cout << "l : " << locked << '\n';
            // cout << "turn : " << turn << '\n';
            // cout << "moves : " << moves << '\n';
            // cout << "result : " << dp[{a, locked}] << '\n';
        }
        // cout << "a : " << a << "\n";
        // cout << "l : " << locked << '\n';
        // cout << "computed dp state e: " << dp[{a, locked}] << '\n';
        return dp[{a, locked}];
    };

    vector<int> locked(n);
    result_slow = dfs(dfs, a, locked, 0);

}

void test(int N, vector<int> A) {
    n = N;
    a = A;

    solve();
    solve_slow();

    if(result_fast != result_slow) {
        cout << "bad n : " << N << " a : " << A << endl;
        cout << "fast result : " << result_fast << " slow result : " << result_slow << endl;
        assert(0);
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int tc; cin >> tc;
    // for(int i = 0; i < tc; i++) {
    //     cin >> n;
    //     a.assign(n, 0);
    //     for(int &x : a) cin >> x;
    //     test(n, a);
    // }

    if(debug) {        
        cin >> n;
        int mx; cin >> mx;
        a.assign(n, 0);
    
        auto dfs = [&](auto self, int idx) -> void {
            if(idx == n) {
                test(n, a);
            } else {
                for(int j = 1; j <= mx; j++) {
                    a[idx] = j;
                    self(self, idx + 1);
                }
            }
        };
    
        dfs(dfs, 0);
        cout << "ALL TESTS PASSED!" << endl;
    } else {
        int casi; cin >> casi;
        while(casi-->0) solve();
    }


    return 0;
}