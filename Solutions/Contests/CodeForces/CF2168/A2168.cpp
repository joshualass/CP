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

    string type; cin >> type;
    if(type == "first") {
        int n; cin >> n;
        string res = "";
        for(int i = 0; i < n; i++) {
            ll num; cin >> num;
            for(int j = 0; j < 7; j++) {
                res.push_back('a' + num % 26);
                num /= 26;
            }
        }
        cout << res << '\n';
    } else {
        string res; cin >> res;
        cout << res.size() / 7 << '\n';
        
        for(int i = 0; i * 7 < res.size(); i++) {
            ll num = 0;
            ll mul = 1;
            for(int j = 0; j < 7; j++) {
                num += (res[i * 7 + j] - 'a') * mul;
                mul *= 26;
            }
            cout << num << " ";
        }
        cout << '\n';
    }

    return 0;
}
