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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;

    map<char,array<int,2>> m;
    vector<int> ch(n, -2);

    array<int,2> pre = {0,-1};
    for(int i = 0; i < n; i++) {
        array<int,2> nx = {-1,-1};
        if(m.count(s[i])) {
            auto [cnt, idx] = m[s[i]];
            // cout << "i : " << i << " cnt : " << cnt << " idx : " << idx << '\n';
            ch[i] = idx;
            nx = {cnt + 1, i};
        }
        // cout << "i : " << i << " Nx : " << nx << '\n';
        if(pre != array<int,2>{-1,-1} && (m.count(s[i]) == 0 || pre > m[s[i]])) {
            // cout << "add nx to char : " << s[i] << '\n';
            m[s[i]] = pre;
        }
        pre = nx;
    }

    // cout << "ch : " << ch << '\n';

    if(ch[n - 1] == -2) {
        cout << "-1\n";
        return 0;
    }

    vector<int> res;
    int cur = n - 1;
    while(cur >= 0) {
        // cout << "cur : " << cur << '\n';
        res.push_back(cur - ch[cur]);
        cur = ch[cur];
    }
    
    reverse(res.begin(), res.end());

    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++) cout << res[i] << " \n"[i == res.size() - 1];

    return 0;
}
