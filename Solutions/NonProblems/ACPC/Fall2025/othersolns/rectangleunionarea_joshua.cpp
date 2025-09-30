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
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //read and compress stuff. 

    int n; cin >> n;
    vector<array<int,4>> a(n);
    set<int> xs, ys;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            cin >> a[i][j];
            int add = j >= 2;
            if(j % 2 == 0) {
                xs.insert(a[i][j] + add);
            } else {
                ys.insert(a[i][j] + add);
            }
        }
    }

    int px = 0, py = 0;
    map<int,int> mx, my;
    vector<int> cx, cy;
    for(int x : xs) {
        cx.push_back(x);
        mx[x] = px++;
    }
    for(int y : ys) {
        cy.push_back(y);
        my[y] = py++;
    }

    vector<array<int,4>> ca(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            int add = (j >= 2);
            if(j % 2 == 0) {
                ca[i][j] = mx[a[i][j] + add];
            } else {
                ca[i][j] = my[a[i][j] + add];
            }
        }
    }

    //construct rm stuff
    vector<vector<int>> rm(xs.size(), vector<int>(ys.size()));
    for(int i = 0; i < n; i++) {
        for(int j = ca[i][0]; j < ca[i][2]; j++) {
            int lo = ca[i][1], hi = ca[i][3];
            rm[j][lo]++;
            rm[j][hi]--;
        }
    }

    // cout << "rm\n" << rm << '\n';

    for(int i = 0; i < px; i++) {
        int cur = 0;
        for(int j = 0; j < py; j++) {
            cur += rm[i][j];
            rm[i][j] = (bool) cur;
        }
        int latest;
        for(int j = py - 1; j >= 0; j--) {
            if(rm[i][j] == 0) latest = j;
            if(j == py - 1) assert(rm[i][j] == 0);
            rm[i][j] = latest;
        }
    }

    // cout << "rm final\n" << rm << '\n';

    //rm is constructed, now do some monotonic stack things
    ll res = 0;

    auto upd_max = [&](int x1, int x2, int y1, int y2) -> void {
        res = max(res, 1LL * (cx[x2] - cx[x1]) * (cy[y2] - cy[y1]));
    };

    for(int col = 0; col < py; col++) {
        //stack stores {row, latest column}
        stack<array<int,2>> st;
        for(int row = 0; row < px; row++) {
            int hi = rm[row][col];
            int push_row = row;
            while(st.size() && st.top()[1] > hi) {
                auto [tr, tc] = st.top();
                st.pop();
                upd_max(tr, row, col, tc);
                push_row = tr;
            }
            st.push({push_row, hi});
        }
        assert(st.top()[1] == col);
    }

    cout << res << '\n';

    return 0;
}
