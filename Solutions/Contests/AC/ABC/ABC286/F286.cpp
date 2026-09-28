// #include <algorithm>
// #include <bitset>
// #include <complex>
// #include <deque>
// #include <exception>
// #include <fstream>
// #include <functional>
// #include <iomanip>
// #include <ios>
// #include <iosfwd>
// #include <iostream>
// #include <istream>
// #include <iterator>
// #include <limits>
// #include <list>
// #include <locale>
// #include <map>
// #include <memory>
// #include <new>
// #include <numeric>
// #include <ostream>
// #include <queue>
// #include <set>
// #include <sstream>
// #include <stack>
// #include <stdexcept>
// #include <streambuf>
// #include <string>
// #include <typeinfo>
// #include <utility>
// #include <valarray>
// #include <vector>
// #include <array>
// #include <atomic>
// #include <chrono>
// #include <condition_variable>
// #include <forward_list>
// #include <future>
// #include <initializer_list>
// #include <mutex>
// #include <random>
// #include <ratio>
// #include <regex>
// #include <scoped_allocator>
// #include <system_error>
// #include <thread>
// #include <tuple>
// #include <typeindex>
// #include <type_traits>
// #include <unordered_map>
// #include <unordered_set>
// #include <cassert>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// vector<int> cycles = {4, 9, 5, 7, 11, 13, 17, 19, 23};
// // vector<int> cycles = {2, 3};

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
// ll modInverse(ll b, ll m) {
//     ll x, y;
//     ll g = gcdExtended(b, m, &x, &y);
 
//     if (g != 1) return -1;
 
//     return (x % m + m) % m;
// }
 
// ll gcdExtended(ll a, ll b, ll *x, ll *y) {
//     if (a == 0) {
//         *x = 0, *y = 1;
//         return b;
//     }
 
//     ll x1, y1;
//     ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
//     *x = y1 - (b / a) * x1;
//     *y = x1;
 
//     return gcd;
// }

// array<ll,2> crt(array<ll,2> a, array<ll,2> b) {
//     auto [a1, m1] = a;
//     auto [a2, m2] = b;

//     ll sub = ((a2 - a1) % m2 + m2) % m2;
//     ll inv = modInverse(m1, m2);
//     ll q = inv * sub % m2;
//     ll x = a1 + q * m1;

//     return {x, m1 * m2};

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int m = accumulate(cycles.begin(), cycles.end(), 0);

//     cout << m << endl;
//     int p = 0;
//     for(int i = 0; i < cycles.size(); i++) {
//         int start = p + 1, end = p + cycles[i];
//         for(int j = start + 1; j <= end; j++) cout << j << " ";
//         cout << start << " ";
//         p += cycles[i];
//     }
//     cout << endl;

//     vector<int> b(m);
//     for(int &x : b) cin >> x;
//     array<ll,2> cur;
//     p = 0;
//     for(int i = 0; i < cycles.size(); i++) {
//         int mod = cycles[i];
//         int a = b[p] - 1 - p;

//         // cout << "a : " << a << " mod : " << mod << '\n';
        
//         if(i) {
//             cur = crt(cur, {a, mod});
//         } else {
//             cur = {a, mod};
//         }

//         p += cycles[i];
//         // cout << "cur : " << cur << '\n';
//     }

//     cout << cur[0] << '\n';

//     return 0;
// }


#include <vector>
#include <tuple>
#include <numeric>
#include <iostream>
#include <random>

int main() {
    using namespace std;
    constexpr unsigned long N{9}, M{110}, prod{1338557220};
    const vector<tuple<unsigned long, unsigned long, unsigned long>> v{{0, 4, 334639305}, {4, 13, 594914320}, {13, 18, 1070845776}, {18, 25, 764889840}, {25, 36, 365061060}, {36, 49, 1235591280}, {49, 66, 629909280}, {66, 85, 1056755700}, {85, 108, 640179540}};
    vector<unsigned long> A(M);
    iota(begin(A), end(A), 1UL);
    for (const auto[l, r, _] : v) A[r - 1] = l;
    mt19937_64 mt{random_device{}()};
    uniform_int_distribution<unsigned long> uid(0, M - 1);
    A[108] = uid(mt);
    A[109] = uid(mt);

    cout << M << endl;
    for (const auto r : A) cout << r + 1 << " ";
    cout << endl;

    vector<unsigned long> B(M);
    for (auto &&r : B) cin >> r;

    unsigned long ans{};
    for (const auto[i, _, x] : v) ans += (B[i] - A[i]) * x;
    cout << ans % prod << endl;

    return 0;
}