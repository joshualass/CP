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
#include <bits/stdc++.h>
typedef unsigned long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll m, n; cin >> m >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    a.push_back(0);
    sort(a.rbegin(), a.rend());

    for(int i = 0; i < n; i++) {
        ll need = (a[i] - a[i+1]) * (i + 1);
        if(m < need) {
            ll cur = a[i] - m / (i + 1);
            ll ec = m - m / (i + 1) * (i + 1);
            ll res = 0;
            // cout << "i : " << i << " m : " << m << " need : " << need << " cur : " << cur << " ec : " << ec << '\n';
            for(int j = 0; j < n; j++) {
                ll z;
                if(j <= i) {
                    z = cur;
                    if(j < ec) z--;
                } else {
                    z = a[j];
                }
                // cout << "j : " << j << " z : " << z << endl;
                res += z * z;
            }
            cout << res << '\n';
            return 0;
        } else {
            m -= need;
        }
    }

    return 0;
}
