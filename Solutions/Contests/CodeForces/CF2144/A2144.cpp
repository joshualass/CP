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
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> p(n + 1);

    for(int i = 0; i < n; i++) {
        cin >> p[i+1];
        p[i+1] += p[i];
    }

    int l = 0, r = 0;
    
    for(int i = 1; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int s1 = p[i] % 3, s2 = (p[j] - p[i]) % 3, s3 = (p[n] - p[j]) % 3;
            if(s1 == s2 && s2 == s3 || s1 != s2 && s1 != s3 && s2 != s3) {
                l = i, r = j;
            }
        }
    }

    cout << l << " " << r << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}