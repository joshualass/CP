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

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<int> dx = {1,1,1,0,-1,-1,-1,0}, dy = {1,0,-1,-1,-1,0,1,1};

    queue<array<int,2>> q;

    auto check = [&](int i, int j) -> bool {
        if(a[i][j] != '@') return 0;
        int cnt = 0;
        for(int k = 0; k < 8; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < n && nj >= 0 && nj < a[i].size()) {
                if(a[ni][nj] == '@') cnt++;
            }
        }
        return cnt < 4;
    };

    int res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < a[i].size(); j++) {
            if(check(i, j)) {
                q.push({i, j});
                a[i][j] = '.';
            }
        }
    }

    while(q.size()) {
        auto [i, j] = q.front();
        q.pop();

        res++;

        for(int k = 0; k < 8; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < n && nj >= 0 && nj < a[i].size()) {
                if(check(ni,nj)) {
                    q.push({ni, nj});
                    a[ni][nj] = '.';
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}
