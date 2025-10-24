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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    array<int,3> ct = {}, ci = {}, it = {}, ii = {};
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        if(s[0] == 'N') {
            for(int j = 1; j < 4; j++) {
                ct[j - 1]++;
                if(s[j] == 'Y') {
                    ci[j - 1]++;
                }
            }
        } else {
            for(int j = 1; j < 4; j++) {
                it[j - 1]++;
                if(s[j] == 'Y') {
                    ii[j - 1]++;
                }
            }
        }
    }

    // cout << "ci : " << ci << '\n';
    // cout << "ct : " << ct << '\n';
    // cout << "ii : " << ii << '\n';
    // cout << "it : " << it << "\n";

    for(int i = 0; i < 3; i++) {
        ld c_rate = ((ld) ci[i]) / ct[i];
        ld i_rate = ((ld) ii[i]) / it[i];
        ld delta = c_rate - i_rate;
        if(delta <= 0) {
            cout << "Not Effective\n";
        } else {
            cout << fixed << setprecision(10) << (1 - i_rate / c_rate) * 100 << '\n';
        }
    }

    return 0;
}
