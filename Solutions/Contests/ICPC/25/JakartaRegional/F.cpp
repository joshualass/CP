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

vector<int> s1, s2;
ll p, q;

void solve_s1(int n, vector<vector<int>>& c) {
    auto is_valid = [&](int val) -> vector<int> {
        vector<int> deg(n, 0);
        for(int i = 0; i < n; i++) {
            for(int x : c[i]) deg[x] ++;
        }
        vector<bool> v(n, false);
        while(true) {
            bool done = true;
            for(int i = 0; i < n; i++) {
                if(!v[i] && deg[i] < val) {
                    v[i] = true;
                    done = false;
                    for(int x : c[i]) deg[x] --;
                }
            }
            if(done) break;
        }
        vector<int> s;
        for(int i = 0; i < n; i++) if(!v[i]) s.push_back(i);
        return s;
    };
    int low = 0, high = n;
    int ans = 0;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(mid).size() != 0) {
            ans = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    s1 = is_valid(ans);
    p = ans;
}

void solve_s2(int n, vector<vector<int>>& c) {
    vector<int> deg(n, 0);
    for(int i = 0; i < n; i++) {
        for(int x : c[i]) deg[x] ++;
    }
    vector<int> s;
    vector<bool> v(n, false);
    while(true) {
        int minind = -1, mindeg = 1e9;
        for(int i = 0; i < n; i++) {
            if(v[i]) continue;
            if(deg[i] < mindeg) {
                mindeg = deg[i];
                minind = i;
            }
        }
        if(minind == -1) break;
        v[minind] = true;
        for(int x : c[minind]) {
            v[x] = true;
        }
        s.push_back(minind);
    }
    s2 = s;
    q = s.size();
}

void solve_s2_2(int n, vector<vector<int>>& c) {
    vector<int> s;
    vector<int> col(n, -1);
    for(int i = 0; i < n; i++) {
        // cout << "BIPARTITE" << endl;
        if(col[i] != -1) continue;
        queue<int> q;
        vector<int> zs, os;
        int zcnt = 0, ocnt = 0;
        col[i] = 0;
        q.push(i);
        while(q.size() != 0) {
            int cur = q.front();
            q.pop();
            if(col[cur] == 0) {
                zs.push_back(cur);
                zcnt ++;
            }
            else {
                os.push_back(cur);
                ocnt ++;
            }
            for(int x : c[cur]) {
                if(col[x] != -1 && col[x] != (col[cur] ^ 1)) {
                    return;
                }
                if(col[x] == -1) q.push(x);
                col[x] = col[cur] ^ 1;
            }
        }
        if(zcnt > ocnt) {
            for(int x : zs) s.push_back(x);
        }
        else {
            for(int x : os) s.push_back(x);
        }
    }
    if(s.size() > s2.size()) {
        s2 = s;
        q = s.size();
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        c[u].push_back(v);
        c[v].push_back(u);
    }

    solve_s1(n, c);
    solve_s2(n, c);
    solve_s2_2(n, c);

    // assert((p + 1) * (q + 1) > n);
    cout << p << " " << q << "\n";
    cout << s1.size() << " ";
    for(int x : s1) cout << (x + 1) << " ";
    cout << "\n";
    cout << s2.size() << " ";
    for(int x : s2) cout << (x + 1) << " ";
    cout << "\n";

    return 0;
}
