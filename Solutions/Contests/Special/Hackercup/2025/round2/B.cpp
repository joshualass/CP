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
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// void solve() {

//     int n, m; cin >> n >> m;
//     map<int,int> ma;
//     vector<int> b(m);

//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         ma[x]++;
//     }

//     vector<int> a;
//     for(auto [k, v] : ma) a.push_back(v);
//     reverse(a.begin(), a.end());

//     for(int &x : b) cin >> x;
//     sort(b.begin(), b.end());

//     // cout << "a : " << a << endl;
//     // cout << "b : " << b << endl;

//     int l = -1, r = a.size() - 1;
//     while(l != r) {
//         int m = (l + r + 1) / 2;
//         ll cnt = 0, need = 0; //cnt is the current count of things under, need is how many we need. 
//         int ok = 1; // flag
//         int p = 0, len = 0; 
//         int under = accumulate(a.begin(), a.begin() + m + 1, 0);
//         // cout << "under : " << under << endl;
//         // cout << "testing m : " << m << endl;
//         for(int i = 0; i <= m; i++) {
//             need += under;
//             // under -= a[((int) a.size()) - m - 1 + i];
//             // len += a[((int) a.size()) - m - 1 + i];
//             under -= a[i];
//             len += a[i];
//             while(p < b.size() && b[p] <= len) {
//                 cnt += b[p++];
//             }
//             ll test = cnt + 1LL * (b.size() - p) * len;
//             // cout << "i : " << i << " need : " << need << " test : " << test << endl;
//             if(test < need) ok = 0;
//         }
//         if(ok) {
//             l = m;
//         } else {
//             r = m - 1;
//         }
//     }
//     int res = 0;
//     for(int i = 0; i <= l; i++) res += a[i];
//     cout << res << '\n';
// }

void solve() {
    int n, m; cin >> n >> m;
    map<int,int> ma;
    vector<int> b(m);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ma[x]++;
    }
    for(int &x : b) cin >> x;
    vector<int> a;
    for(auto [k, v] : ma) a.push_back(v);
    reverse(a.begin(), a.end());
    sort(b.begin(), b.end());
    int l = -1, r = a.size() - 1;
    while(l != r) {
        int m = (l + r + 1) / 2;
        ll need = 0;
        int under = accumulate(a.begin(), a.begin() + m + 1, 0);
        ll have = 0;
        int p = 0, len = 0;
        int ok = 1;
        // cout << "testing m : " << m << '\n';
        for(int i = 0; i <= m; i++) {
            need += under;
            int cnt = a[m-i];
            under -= cnt;
            len += cnt;
            while(p < b.size() && b[p] <= len) {
                have += b[p++];
            }
            ll total = have + 1LL * (b.size() - p) * len;
            if(total < need) ok = 0;
            // cout << "i : " << i << " need : " << need << " have : " << have << " total : " << total << '\n';
        }
        if(ok) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    int res = 0;
    for(int i = 0; i <= l; i++) res += a[i];
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    freopen("Bin.txt","r",stdin);
    freopen("Bout.txt","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}