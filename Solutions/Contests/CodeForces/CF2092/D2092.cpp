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

/*
LLITT
LLTITT
LLITITT
LLITILTT
LLITILITT

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        if(s[i] == 'I') a[i] = 1;
        if(s[i] == 'T') a[i] = 2;
    }
    vector<int> ops;
    auto add_op = [&](int idx) -> void {
        ops.push_back(idx);
        assert(idx && a[idx-1] != a[idx]);
        vector<int> vis(3);
        vis[a[idx-1]] = 1;
        vis[a[idx]] = 1;
        for(int i = 0; i < 3; i++) {
            if(vis[i] == 0) a.insert(a.begin() + idx, i);
        }
    };

    while(1) {
        // cout << "a : " << a << endl;
        int f = 0;
        array<int,3> cnts = {};
        for(int i = 0; i < 3; i++) cnts[i] = count(a.begin(), a.end(), i);
        if(cnts[0] == cnts[1] && cnts[0] == cnts[2]) break;
        int mx = *max_element(cnts.begin(), cnts.end());
        for(int i = 0; i < a.size(); i++) {
            if(cnts[a[i]] == mx) {
                if(i && a[i-1] != a[i]) {
                    f = 1;
                    add_op(i);
                    add_op(i + 1);
                    break;
                }
                if(i + 1 < a.size() && a[i] != a[i+1]) {
                    f = 1;
                    add_op(i+1);
                    add_op(i+1);
                    break;
                }
            }
        }
        
        if(f == 0) {
            // cout << "no good!" << endl;
            cout << "-1\n";
            return;
        }
    }
    cout << ops.size() << '\n';
    for(int x : ops) cout << x << '\n';
}

// void solve() {
    
//     int n; cin >> n;
//     string s; cin >> s;


//     vector<int> ops;
//     while(1) {
//         int lc = count(s.begin(), s.end(), 'L');
//         int ic = count(s.begin(), s.end(), 'I');
//         int tc = count(s.begin(), s.end(), 'T');
//         int f = 0;
//         if(lc == ic && lc == tc) break;
//         for(int i = 1; i < n; i++) {
//             set<char> ch;
//             ch.insert('L');
//             ch.insert('I');
//             ch.insert('T');
//             ch.erase(s[i-1]);
//             ch.erase(s[i]);
//             if(ch.size() == 1) {
//                 char c = *ch.begin();
//                 if(c == 'L' && lc < max(ic,tc)) {
//                     s.insert(s.begin() + i, 'L');
//                     ops.push_back(i);
//                     f = 1;
//                     break;
//                 }
//                 if(c == 'I' && ic < max(lc, tc)) {
//                     s.insert(s.begin() + i, 'I');
//                     ops.push_back(i);
//                     f = 1;
//                     break;
//                 }
//                 if(c == 'T' && tc < max(lc, ic)) {
//                     s.insert(s.begin() + i, 'T');
//                     ops.push_back(i);
//                     f = 1;
//                     break;
//                 }
//             }
//         }
//         if(!f) {
//             for(int i = 1; i < n; i++) {
//                 set<char> ch;
//                 ch.insert('L');
//                 ch.insert('I');
//                 ch.insert('T');
//                 ch.erase(s[i-1]);
//                 ch.erase(s[i]);
//                 if(ch.size() == 1) {
//                     char c = *ch.begin();
//                     if(c == 'L' && lc <= max(ic,tc)) {
//                         s.insert(s.begin() + i, 'L');
//                         ops.push_back(i);
//                         f = 1;
//                         break;
//                     }
//                     if(c == 'I' && ic <= max(lc, tc)) {
//                         s.insert(s.begin() + i, 'I');
//                         ops.push_back(i);
//                         f = 1;
//                         break;
//                     }
//                     if(c == 'T' && tc <= max(lc, ic)) {
//                         s.insert(s.begin() + i, 'T');
//                         ops.push_back(i);
//                         f = 1;
//                         break;
//                     }
//                 }
//             }
//             if(!f) {
//                 cout << "-1\n";
//                 return;
//             }
//         }
//     }

//     cout << ops.size() << '\n';
//     for(int x : ops) cout << x << '\n';

// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}