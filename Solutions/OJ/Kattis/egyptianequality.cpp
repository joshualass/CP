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

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    auto check = [&](vector<array<int,2>> order) -> vector<string> {
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            for(char c : a[i]) if(c == 'C') cnt++;
        }
        if(cnt & 1) return {};
        vector<string> res(n, string(n * 2 - 1, '.'));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n - i - 1; j++) {
                res[j][i] = '#';
                res[j][n * 2 - 2 - i] = '#';
            }
        }
        // for(auto x : res) cout << x << '\n';
        int cur = 0;
        for(auto [x, y] : order) {
            res[x][y] = 'A';
            if(a[x][y] == 'C') cur++;
            if(cur * 2 == cnt) break;
        }
        if(cur * 2 != cnt) return {};
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n * 2 - 1; j++) {
                if(res[i][j] == '.') res[i][j] = 'B';
            }
        }
        return res;
    };

    vector<array<int,2>> o1, o2, o3;
    for(int i = 0; i + 1 < n; i++) {
        for(int j = 0; j >= -i; j--) {
            o1.push_back({i, n - 1 + j});
        }
        for(int j = 1; j <= i; j++) {
            o1.push_back({i, n - 1 + j});
        }
    }

    for(int i = 0; i <= (n - 2) * 2; i++) {
        for(int j = 0; j <= min(i, n * 2 - 4 - i); j++) {
            o2.push_back({n - j - 1, i});
            o3.push_back({n - j - 1, n * 2 - 2 - i});
        }
    }

    // cout << "o1\n" << o1 << endl;
    // cout << "o2\n" << o2 << endl;
    // cout << "o3\n" << o3 << endl;

    auto a1 = check(o1);
    auto a2 = check(o2);
    auto a3 = check(o3);

    vector<string> res;
    if(a1.size()) res = a1;
    if(a2.size()) res = a2;
    if(a3.size()) res = a3;

    if(res.empty()) {
        cout << "impossible\n";
    } else {
        for(auto x : res) cout << x << '\n';
    }

    return 0;
}
