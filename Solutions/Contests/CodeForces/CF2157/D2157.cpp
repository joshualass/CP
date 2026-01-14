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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll n, l, r; cin >> n >> l >> r;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());

    deque<ll> q;
    for(ll x : a) q.push_back(x);

    vector<ll> lefts, rights;
    while(q.size() && q.front() <= l) {
        lefts.push_back(q.front());
        q.pop_front();
    }
    while(q.size() && q.back() >= r) {
        rights.push_back(q.back());
        q.pop_back();
    }

    while(q.size() && lefts.size() != rights.size()) {
        if(lefts.size() > rights.size()) {
            rights.push_back(q.back());
            q.pop_back();
        } else {
            lefts.push_back(q.front());
            q.pop_front();     
        }
    }

    while(q.size() >= 2) {
        lefts.push_back(q.front());
        q.pop_front();
        rights.push_back(q.back());
        q.pop_back();
    }

    // cout << "lefts : " << lefts << '\n';
    // cout << "rights : " << rights << '\n';

    ll res = 0;
    for(int i = 0; i < min(lefts.size(), rights.size()); i++) {
        res += rights[rights.size() - i - 1] - lefts[lefts.size() - i - 1];
    }

    if(lefts.size() > rights.size()) {
        for(int i = 0; i < lefts.size() - rights.size(); i++) {
            res += l - lefts[i];
        }
    } else {
        for(int i = 0; i < rights.size() - lefts.size(); i++) {
            res += rights[i] - r;
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}