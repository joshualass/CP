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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    int ok = 1;
    vector<vector<int>> res(n, vector<int>(n, -1));
    for(int i = 0; i < n; i++) {
        res[i][a[i]] = 0;
    }

    int cnt = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(res[i][j] != res[j][i]) ok = 0;
            if(i == j && res[i][j] == 0) cnt++;
        }
    }

    if((n & 1) && cnt != 1) {
        cout << "No\n";
        return;
    }

    cout << "res start\n" << res << '\n';

    for(int i = 1; i < n; i++) {
        vector<int> vis(n);
        if(n & 1) {
            for(int j = 0; j < n; j++) {
                if(res[j][j] == -1) {
                    vis[j] = 1;
                    res[j][j] = i;
                    break;
                }
            }
        } else {
            if(i == 1) {
                for(int j = 0; j < n; j++) {
                    if(res[j][j] == -1) {
                        vis[j] = 1;
                        res[j][j] = i;
                    }
                }
            }
        }
        for(int j = 0; j < n; j++) {
            if(vis[j] == 0) {
                for(int k = j + 1; k < n; k++) {
                    if(vis[k] == 0 && res[j][k] == -1) {
                        vis[j] = 1;
                        vis[k] = 1;
                        res[j][k] = i;
                        res[k][j] = i;
                        break;
                    }
                }
            }
        }
        if(!(count(vis.begin(), vis.end(), 1) == n)) {
            cout << "bad i : " << i << '\n';
            cout << "current res\n";
            cout << res << '\n';
            assert(count(vis.begin(), vis.end(), 1) == n);
        }
    }

    cout << "Yes\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) cout << res[i][j] + 1 << " \n"[j == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}