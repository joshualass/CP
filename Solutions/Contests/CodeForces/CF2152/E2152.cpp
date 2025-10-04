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

    auto ask = [&](vector<int> a) -> vector<int> {
        cout << "? " << a.size();
        for(int x : a) cout << " " << x + 1;
        cout << endl;
        int c; cin >> c;
        vector<int> b(c);
        for(int &x : b) {
            cin >> x;
            x--;
        }
        return b;
    };

    vector<int> hit(n * n + 1);
    vector<int> res(n + 1, -1);

    vector<vector<int>> ch(n * n + 1);

    for(int i = 0; i < n; i++) {
        vector<int> q;
        for(int j = 0; j < n * n + 1; j++) {
            if(hit[j] == 0) {
                q.push_back(j);
            }
        }

        vector<int> ans = ask(q);
        if(ans.size() >= n + 1) {
            for(int j = 0; j < n + 1; j++) {
                res[j] = ans[j];
            }
            break;
        }

        int phit = n * n + 1;

        for(int j = ans.size() - 1; j >= 0; j--) {
            int idx = ans[j];
            for(int k = idx + 1; k < phit; k++) {
                if(hit[k] == 0) ch[idx].push_back(k);
            }
            phit = idx;
        }

        for(int x : ans) hit[x] = 1;

    }

    vector<int> dec(n * n + 1, 0);
    vector<int> best_ch(n * n + 1, -1);

    for(int i = n * n; i >= 0; i--) {
        for(int c : ch[i]) {
            if(best_ch[i] == -1 || dec[c] > dec[best_ch[i]]) {
                best_ch[i] = c;
            }
        }
        if(best_ch[i] != -1) dec[i] = dec[best_ch[i]];
        dec[i]++;
    }

    for(int i = 0; i < n * n + 1; i++) {
        if(dec[i] >= n + 1) {
            int cur = i;
            for(int j = 0; j < n + 1; j++) {
                res[j] = cur;
                cur = best_ch[cur];
            }
            break;
        }
    }

    assert(res[0] != -1);

    cout << "!";
    for(int x : res) cout << " " << x + 1;
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}