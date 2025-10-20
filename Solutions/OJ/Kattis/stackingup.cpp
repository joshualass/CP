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

    auto f = [&](int targ) -> pair<string, int> {
        int ops = 0;
        string res = "";
        for(int bit = 30; bit >= 0; bit--) {
            if((targ >> bit) & 1) {
                res.push_back('1');
                if(res.size() >= 2) {
                    res.push_back('+');
                    ops++;
                }
            }
            if(res.size() && bit) {
                res.push_back('d');
                res.push_back('+');
                ops++;
            }
        }
        // cout << "targ : " << targ << " res : " << res << '\n';
        return {res, ops};
    };

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int post_ops = 0;
    vector<string> res;
    for(int i = n - 1; i >= 0; i--) {
        // cout << "i : " << i << " post_ops : " << post_ops << '\n';
        auto [s, ops] = f(a[i] + post_ops);
        res.push_back(s);
        post_ops += ops;
    }

    reverse(res.begin(), res.end());
    for(auto x : res) cout << x;
    cout << '\n';

    return 0;
}
