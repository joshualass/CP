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

void solve() {
    
    // int n, k; cin >> n >> k;
    // vector<int> a(n);
    // for(int &x : a) cin >> x;
    // while(1) {
    //     int idx = -1;
    //     for(int i = 0; i < a.size(); i++) {
    //         if(a[i] == 0) {
    //             idx = i;
    //             break;
    //         }
    //     }
    //     if(idx == -1) {
    //         cout << "YES\n";
    //         return;
    //     }
    //     idx = min(idx, ((int) a.size()) - k);
    //     if(idx < 0) {
    //         cout << "NO\n";
    //         return;
    //     }
    //     int num = *max_element(a.begin() + idx, a.begin() + idx + k);
    //     a.erase(a.begin() + idx, a.begin() + idx + k);
    //     a.insert(a.begin() + idx, num);
    // }

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    cout << (count(a.begin(), a.end(), 1) ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}