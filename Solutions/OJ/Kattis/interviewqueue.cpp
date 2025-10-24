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

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> ans;
    vector<int> pv(n, -1), nx(n, -1);
    vector<int> to_rem(0);
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++) {
        if((i != 0 && a[i] < a[i - 1]) || (i != n - 1 && a[i] < a[i + 1])) {
            to_rem.push_back(i);
            v[i] = true;
        }
        pv[i] = i - 1;
        nx[i] = i + 1; 
    }
    while(to_rem.size() != 0) {
        ans.push_back(to_rem);
        set<int> nto_rem;
        for(int x : to_rem) {
            int l = pv[x], r = nx[x];
            if(r != n) pv[r] = pv[x];
            if(l != -1) nx[l] = nx[x];
            if(l == -1 || r == n) continue;
            if(v[l] || v[r]) continue;
            if(a[l] < a[r]) nto_rem.insert(l);
            if(a[r] < a[l]) nto_rem.insert(r);
        }
        to_rem.clear();
        for(int x : nto_rem) {
            to_rem.push_back(x);
            v[x] = true;
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        for(int x : ans[i]) cout << a[x] << " ";
        cout << "\n";
    }
    for(int i = 0; i < n; i++) if(!v[i]) cout << a[i] << " ";
    cout << "\n";

    return 0;
}
