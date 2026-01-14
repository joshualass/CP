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

//4744966219

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << (x == -1e9 ? 8 : x) << " ";
    return os;
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

const ll MAXN = 1500;
const ll MAXM = 1500;

static ll bit2d[MAXN][MAXM];

void update(ll r, ll c, ll val) {
    ++r; ++c;
    for (ll x = r; x <= MAXN; x += x & -x) {
        for (ll y = c; y <= MAXM; y += y & -y) {
            bit2d[x][y] += val;
        }
    }
}

ll query_prefix(ll r, ll c) {
    // cout << "qp called with r : " << r << " c : " << c << '\n';
    if (r < 0 || c < 0) return 0;
    ++r; ++c;
    ll sum = 0;
    for (ll x = r; x > 0; x -= x & -x) {
        for (ll y = c; y > 0; y -= y & -y) {
            sum += bit2d[x][y];
        }
    }
    return sum;
}

ll query(ll r, ll c) {
    return query_prefix(r, c);
}

ll query(ll r1, ll c1, ll r2, ll c2) {
    return query_prefix(r2, c2)
         - query_prefix(r2, c1 - 1)
         - query_prefix(r1 - 1, c2)
         + query_prefix(r1 - 1, c1 - 1);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // update(2, 3, 1);
    // for(int i = 0; i < 4; i++) {
    //     for(int j = 0; j < 4; j++) {
    //         cout << "query i : " << i << " j : " << j << " res : " << query(i, j) << '\n';
    //     }
    // }
    // update(2,3,-1);

    ll n; cin >> n;
    vector<array<ll,2>> a(n);
    for(ll i = 0; i < n; i++) {
        string s; cin >> s;
        ll mid = -1;
        for(ll j = 0; j < s.size(); j++) {
            if(s[j] == ',') {
                mid = j;
                break;
            }
        }
        ll l = stoi(s.substr(0, mid)), r = stoi(s.substr(mid + 1));
        a[i] = {l, r};
    }

    //part 1
    ll res1 = 0;
    for(ll i = 0; i < n; i++) {
        for(ll j = i + 1; j < n; j++) {
            res1 = max(res1, 1LL * (abs(a[i][0] - a[j][0]) + 1) * (abs(a[i][1] - a[j][1]) + 1));
        }
    }

    cout << "part 1 : " << res1 << '\n';

    set<ll> xs, ys;
    for(ll i = 0; i < n; i++) {
        for(int j = -1; j <= 1; j++) {
            xs.insert(a[i][0] + j);
            ys.insert(a[i][1] + j);
        }
    }

    map<ll,ll> mx, my;
    ll p = 0;
    for(ll x : xs) mx[x] = p++;
    p = 0;
    for(ll y : ys) my[y] = p++;

    vector<array<ll,2>> ap;
    for(ll i = 0; i < n; i++) ap.push_back({mx[a[i][0]], my[a[i][1]]});

    vector<vector<ll>> b(xs.size(), vector<ll>(ys.size()));

    auto pall = [&](ll i, ll j) -> void {
        auto lo = ap[i], hi = ap[j];    
        if(lo[0] != hi[0]) {
            if(lo[0] > hi[0]) swap(lo, hi);
            for(ll k = lo[0]; k <= hi[0]; k++) {
                b[k][lo[1]] = 1;
            }
        } else {
            if(lo[1] > hi[1]) swap(lo, hi);
            for(ll k = lo[1]; k <= hi[1]; k++) {
                b[lo[0]][k] = 1;
            }
        }
    };

    for(ll i = 0; i < n; i++) pall(i, (i + 1) % n);

    cout << "b after pall\n";
    for(ll i = 0; i < b.size(); i++) cout << b[i] << '\n';

    vector<ll> dx = {1,-1,0,0}, dy = {0,0,1,-1};
    queue<array<ll,2>> q;

    auto pushq = [&](ll i, ll j) -> void {
        if(b[i][j]) return;
        b[i][j] = -1e9;
        q.push({i, j});
    };

    pushq(0,0);

    while(q.size()) {
        auto [i, j] = q.front();
        q.pop();
        for(ll k = 0; k < 4; k++) {
            ll ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < b.size() && nj >= 0 && nj < b[ni].size() && b[ni][nj] != 1) pushq(ni, nj);
        }
    }

    for(ll i = 0; i < b.size(); i++) cout << b[i] << '\n';

    // cout << "xs sz : " << xs.size() << '\n';
    // cout << "ys sz : " << ys.size() << '\n';

    for(ll i = 0; i < b.size(); i++) {
        for(ll j = 0; j < b[i].size(); j++) {
            update(i, j, b[i][j]);
        }
    }

    // cout << query(8, 7) << '\n';
    // cout << query(3, 0) << '\n';
    // cout << query(3, 7) << '\n';
    // cout << query(8, 0) << '\n';

    ll res = 0;
    for(ll i = 0; i < n; i++) {
        for(ll j = i + 1; j < n; j++) {
            auto [li, ri] = ap[i];
            auto [lj, rj] = ap[j];
            ll l1 = min(li,lj), l2 = max(li,lj), r1 = min(ri,rj), r2 = max(ri,rj);
            ll qv = query(l1, r1, l2, r2);
            if(qv >= 0) {
                // cout << "these coordinates are possible i coord : " << a[i] << " j coord : " << a[j] << '\n';
                // cout << "compressed coords i : " << li << ", " << ri << " coords j : " << lj << ", " << rj << " qv : " << qv << '\n';
                res = max(res, 1LL * (abs(a[i][0] - a[j][0]) + 1) * (abs(a[i][1] - a[j][1]) + 1));
            }
        }
    }

    cout << "part 2 res : " << res << '\n';

    return 0;
}
