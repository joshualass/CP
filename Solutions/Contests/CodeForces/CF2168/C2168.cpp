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
vector<int> a(1 << 15), ra(1 << 16);

void solve_first() {
    int x; cin >> x;
    x--;

    vector<int> res;
    int cur = 0;
    int num = a[x];
    for(int bit = 0; bit < 16; bit++) {
        if((num >> bit) & 1) {
            res.push_back(bit);
            cur ^= bit;
        }
    }

    for(int i = 0; i < 4; i++) {
        if((cur >> i) & 1) res.push_back(i + 16);
    }

    cout << res.size() << '\n';
    for(int x : res) cout << x + 1 << " ";
    cout << '\n';

}

void solve_second() {

    int n; cin >> n;
    vector<int> bm(20);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        bm[x - 1] = 1;
    }

    int cnt = 0;
    for(int i = 0; i < 16; i++) {
        if(bm[i]) cnt++;
    }

    if(cnt & 1) {
        int cur = 0;
        for(int i = 0; i < 16; i++) {
            if(bm[i]) cur ^= i;
        }
        int targ = 0;
        for(int i = 16; i < 20; i++) {
            if(bm[i]) targ += 1 << (i - 16);
        }
        bm[cur ^ targ] ^= 1;
    }

    int cur = 0;
    for(int i = 0; i < 16; i++) {
        if(bm[i]) cur += 1 << i;
    }

    cout << ra[cur] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cur = 0;
    for(int i = 0; i < 1 << 16; i++) {
        if(__builtin_popcount(i) % 2 == 0) {
            a[cur] = i;
            ra[i] = cur;
            cur++;
        }
    }

    string type; cin >> type;
    int casi; cin >> casi;
    while(casi-->0) {
        if(type == "first") {
            solve_first();
        } else {
            solve_second();
        }
    }

    return 0;
}