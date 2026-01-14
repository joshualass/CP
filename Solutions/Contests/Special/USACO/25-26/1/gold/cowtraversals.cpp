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
    vector<int> to(n);
    vector<vector<int>> radj(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        to[i] = x;
        radj[x].push_back(i);
    }

    vector<int> isroot(n, 1);
    vector<int> degs(n);
    queue<int> q;
    for(int i = 0; i < n; i++) {
        degs[i] = radj[i].size();
        if(degs[i] == 0) {
            q.push(i);
        }
    }

    while(1) {
        int x = q.front();
        q.pop();

        isroot[x] = 0;
        degs[to[x]]--;
        if(degs[to[x]] == 0) q.push(to[x]);
    }

    

    return 0;
}
