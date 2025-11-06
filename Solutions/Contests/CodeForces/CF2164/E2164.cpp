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

const int N = 1e6;
int dsu[N];
int sizes[N];
priority_queue<array<int,2>> pqs[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 0;
        while(pqs[i].size()) pqs[i].pop();
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
    //move y to x
    if(pqs[y].size() > pqs[x].size()) {
        swap(x, y);
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
    while(pqs[y].size()) {
        pqs[x].push(pqs[y].top());
        pqs[y].pop();
    }
}

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

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> p(n);
    ll res = 0;

    vector<array<int,3>> e;
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        e.push_back({u, v, w});
        p[u] ^= 1;
        p[v] ^= 1;
        res += w;
    }

    dsubuild(n);
    for(int i = 0; i < n; i++) {
        if(p[i]) sizes[i]++;
    }

    for(auto [u, v, w] : e) {
        merge(u, v);
        u = find(u);
        int cnt = sizes[u] / 2;
        sizes[u] -= cnt * 2;
        while(pqs[u].size() && pqs[u].top()[0] >= w) {
            auto [w, c] = pqs[u].top();
            pqs[u].pop();
            res -= 1LL * w * c;
            cnt += c;
        }
        res += 1LL * w * cnt;
        pqs[u].push({w, cnt});
    }

    cout << res << '\n';

    // vector<array<int,2>> st;

    // ll res = 0;
    // vector<array<int,2>> e;
    // vector<array<int,3>> wtf;

    // for(int i = 0; i < m; i++) {
    //     int u, v, w; cin >> u >> v >> w;
    //     u--; v--;
    //     e.push_back({u, v});
    //     wtf.push_back({w, u, v});
    //     // cout << "u : " << u << " v : " << v << " w : " << w << endl;
    //     p[u] ^= 1;
    //     p[v] ^= 1;
    //     res += w;
    //     while(st.size() && st.back()[0] > w) {
    //         st.pop_back();
    //     }
    //     st.push_back({w, i});
    // }

    // // cout << "p : " << p << '\n';
    // // cout << "st : " << st << '\n';

    // for(int i = 0; i < n; i++) {
    //     if(p[i] & 1) sizes[find(i)]++;
    // }   

    // int ptr = 0, p2 = 0;
    // sort(wtf.begin(), wtf.end());

    // auto ttfang = [&](int u, int v, int w) -> void {
    //     merge(u, v);
    //     u = find(u);
    //     while(sizes[u] >= 2) {
    //         sizes[u] -= 2;
    //         res += w;
    //     }
    // };

    // for(auto [w, idx] : st) {
    //     while(p2 < m && wtf[p2][0] <= w) {
    //         ttfang(wtf[p2][1], wtf[p2][2], wtf[p2][0]);
    //         p2++;
    //     }
    //     while(ptr <= idx) {
    //         merge(e[ptr][0], e[ptr][1]);
    //         ptr++;
    //     }
    //     ttfang(e[idx][0], e[idx][1], w);
    // }

    // cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}