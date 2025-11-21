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

    int n; cin >> n;
    bitset<100000> bad {};
    bitset<100000> idxs {};

    map<int, vector<int>> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x].push_back(i);
    }

    for(auto it = m.rbegin(); it != m.rend(); it++) {
        auto [_, b] = *it;

        // cout << "b : " << b << '\n';

        for(int i : b) {
            bad |= idxs << (100000 - i);
        }

        for(int i : b) {
            // cout << "mark bad : " << i << '\n';
            idxs[i] = 1;
        }
    }

    // for(int i = 0; i < 100000; i++) {
    //     if(bad[i]) cout << "i : " << i << " is bad!\n";
    // }

    for(int i = 99999; 99999 - i < n; i--) {
        if(bad[i] == 0) cout << 100000 - i << " ";
    }

    cout << '\n';

    return 0;
}
