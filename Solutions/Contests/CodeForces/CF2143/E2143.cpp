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
    string s; cin >> s;
    int a = 0, b = 0, c = 0, d = 0, cur = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            cur++;
            if(i & 1) {
                b++;
            } else {
                a++;
            }
        } else {
            cur--;
            if(i & 1) {
                d++;
            } else {
                c++;
            }
        }
    }

    if(cur % 4 != 0 || a == 0 && d == 0) {
        cout << "-1\n";
        return;
    }

    int need = (n / 2 - (a + b)) / 2;
    a += need;
    b += need;
    c -= need;
    d -= need;

    int pref_len = min((a * 2) - 1, b * 2);
    a -= (pref_len + 1) / 2;
    b -= pref_len / 2;
    c -= pref_len / 2;
    d -= (pref_len + 1) / 2;

    string res = string(pref_len, '(');
    while(a || b || c || d) {
        if(res.size() & 1) {
            if(b) {
                b--;
                res.push_back('(');
            } else {
                d--;
                res.push_back(')');
            }
        } else {
            if(a) {
                a--;
                res.push_back('(');
            } else {
                c--;
                res.push_back(')');
            }
        }
    }

    cout << res + string(pref_len, ')') << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}