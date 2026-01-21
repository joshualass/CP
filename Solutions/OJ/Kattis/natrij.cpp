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

    string cur, explode; cin >> cur >> explode;

    auto parse_time = [](string s) -> int {
        int hr = stoi(s.substr(0,2)), min = stoi(s.substr(3,2)), sec = stoi(s.substr(6,2));
        return hr * 3600 + min * 60 + sec;
    };

    int ct = parse_time(cur);
    int et = parse_time(explode);
    if(ct >= et) et += 24 * 3600;
    int time = et - ct;
    int hr = time / 3600, min = time / 60 % 60, sec = time % 60;

    auto print_2 = [](int x) -> void {
        string s = to_string(x);
        if(s.size() == 1) s.insert(s.begin(), '0');
        cout << s;
    };
    print_2(hr);
    cout << ":";
    print_2(min);
    cout << ":";
    print_2(sec);
    cout << '\n';

    return 0;
}
