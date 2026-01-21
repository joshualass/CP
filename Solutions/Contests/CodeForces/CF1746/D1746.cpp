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

void solve() {
    
    ll n, k; cin >> n >> k;
    vector<vector<int>> ch(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        ch[p].push_back(i);
    }
    vector<ll> s(n);
    for(ll &x : s) cin >> x;

    vector<priority_queue<array<ll,2>>> pqs(n);
    vector<ll> best(n);

    auto dfspq = [&](auto self, int i, ll pw) -> void {
        s[i] += pw;
        if(ch[i].empty()) {
            best[i] = s[i];
        } else {
            for(int c : ch[i]) {
                self(self, c, s[i]);
                pqs[i].push({best[c], c});
            }
            best[i] = pqs[i].top()[0];
        }
    };

    dfspq(dfspq, 0, 0);
    ll res = 0;

    auto dfs_flow = [&](auto self, int i, ll flow) -> void {
        if(ch[i].empty()) {
            res += s[i] * flow;
        } else {
            ll all = flow / ch[i].size();
            ll ec = flow - all * ch[i].size();
            if(all) {
                pqs[i] = priority_queue<array<ll,2>>();
                for(int c : ch[i]) {
                    self(self, c, all);
                    pqs[i].push({best[c], c});
                }
            }
            while(ec) {
                ec--;
                if(pqs[i].empty()) {
                    for(int c : ch[i]) pqs[i].push({best[c], c});
                } 
                auto [score, c] = pqs[i].top();
                pqs[i].pop();
                self(self, c, 1);
            }
            if(pqs[i].empty()) {
                for(int c : ch[i]) pqs[i].push({best[c], c});
            }
            best[i] = pqs[i].top()[0];
        }
    };

    dfs_flow(dfs_flow, 0, k);
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}