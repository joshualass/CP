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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
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

    string s; cin >> s;

    vector<pair<char,int>> a;
    char p = '\0';
    int cnt = 0;
    for(char c : s) {
        if(p != c) {
            if(p != '\0') {
                a.push_back({p, cnt});
            }
            cnt = 0;
        }
        cnt++;
        p = c;
    }

    a.push_back({p, cnt});

    // cout << "a : " << a << '\n';

    bool cc = 0;
    int res = 0;

    for(auto [ch, c] : a) {
        if(ch == '0') {
            if(c >= 2) cc = 0;
        } else {
            if(c >= 2) {
                if(cc == 0) {
                    cc = 1;
                    res++;
                }
            }
            res++;
        }
    }

    cout << res << '\n';

    return 0;
}
