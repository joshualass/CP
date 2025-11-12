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
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    auto _solve = [](vector<int> a, int l, int r) -> ll {
        //count the number of subarrays where there are an even amount of values <= and >= 
        auto __solve = [](vector<int> a, int l, int r) -> ll {
            vector<int> pos(1, 0), neg;
            int cur = 0;
            for(int i = 0; i < a.size(); i++) {
                if(a[i] <= l) {
                    cur--;
                } else if(a[i] >= r) {
                    cur++;
                } else {
                    assert(0);
                }
                if(cur >= 0) {
                    if(pos.size() <= cur) pos.push_back(0);
                    // cout << "cur : " << cur << " pos size : " << pos.size() << endl;
                    pos[cur]++;
                } else {
                    if(neg.size() <= (-cur - 1)) neg.push_back(0);
                    neg[-cur - 1]++;
                }
            }

            cur = 0;
            ll res = 0;
            for(int i = 0; i < a.size(); i++) {
                if(i) {
                    if(cur >= 0) {
                        pos[cur]--;
                    } else {
                        neg[-cur - 1]--;
                    }
                }
                int cnt;
                if(cur >= 0) {
                    cnt = pos[cur];
                } else {
                    cnt = neg[-cur - 1];
                }
                res += cnt;
                if(a[i] <= l) {
                    cur--;
                } else {
                    cur++;
                }
            }
            return res;
        };

        ll res = 0;
        int p = 0;
        for(int i = 0; i < a.size(); i++) {
            if(l < a[i] && a[i] < r) {
                res += __solve(vector<int>(a.begin() + p, a.begin() + i), l, r);
                p = i + 1;
            }
        }
        res += __solve(vector<int>(a.begin() + p, a.end()), l, r);
        return res;
    };

    ll res = 0;

    for(int i = 1; i <= 9; i++) {
        res += _solve(a, i, i + 1);
    }
    for(int i = 1; i <= 8; i++) {
        res -= _solve(a, i, i + 2);
    }

    cout << 1LL * n * (n + 1) / 2 - res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}