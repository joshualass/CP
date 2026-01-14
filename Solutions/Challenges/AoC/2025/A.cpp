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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n; cin >> n;
    // int cnt = 0;
    // int cur = 50;
    // for(int i = 0; i < n; i++) {
    //     string s; cin >> s;
    //     char dir = s[0];
    //     int num = stoi(s.substr(1));
    //     if(dir == 'L') {
    //         cur = (cur + 100 - num) % 100;
    //     } else {
    //         cur = (cur + num) % 100;
    //     }
    //     if(!cur) cnt++;
    // }

    // cout << cur << '\n';
    // cout << cnt << '\n';

    int n; cin >> n;
    ll res = 0;
    int cur = 50;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        char dir = s[0];
        ll num = stoll(s.substr(1));
        res += num / 100;
        num %= 100;
        if(dir == 'L') {
            if(cur && cur - num <= 0) {
                res++;
            }
            cur -= num;
            cur = (cur + 100) % 100;
        } else {
            if(cur + num >= 100) {
                res++;
            }
            cur = (cur + num) % 100;
        }
    }

    cout << res << '\n';

    return 0;
}
