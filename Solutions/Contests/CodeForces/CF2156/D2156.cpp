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
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;

    auto ask = [&](int idx, int x) -> int {
        cout << "? " << idx + 1 << " " << x << endl;
        int res; cin >> res;
        return res;
    };

    int bit = 0;
    //in is the set of indices that are in. 
    set<int> vals, idxs;
    for(int i = 1; i <= n; i++) vals.insert(i);
    for(int j = 0; j + 1 < n; j++) idxs.insert(j);
    while(idxs.size()) {
        // cout << "before prune\n";
        // cout << "debug vals : " << vals << '\n';
        // cout << "debug idxs : " << idxs << '\n';
        int sum = 0, exp = 0;
        map<int,int> m;
        for(int x : idxs) {
            int res = ask(x, 1 << bit);
            m[x] = res;
            sum += res;
        }
        for(int x : vals) {
            if((x >> bit) & 1) {
                exp++;
            }
        }
        //the number of 1 bits is correct, then the bad is among the 0 bits


        // cout << "debug sum : " << sum << " exp : " << exp << '\n';

        if(sum == exp) {
            for(auto [k, v] : m) {
                if(v == 1) {
                    idxs.erase(k);
                }
            }
            vector<int> togo;
            for(int x : vals) {
                if(((x >> bit) & 1)) {
                    togo.push_back(x);
                }
            }
            for(int x : togo) vals.erase(x);
        } else {
            for(auto [k, v] : m) {
                if(v == 0) {
                    idxs.erase(k);
                }
            }
            vector<int> togo;
            for(int x : vals) {
                if(((x >> bit) & 1) == 0) {
                    togo.push_back(x);
                }
            }
            for(int x : togo) vals.erase(x);
        }
        bit++;
        // cout << "pruning now\n";
        // cout << "debug vals : " << vals << '\n';
        // cout << "debug idxs : " << idxs << '\n';
        // cout << "debug sum : " << sum << " exp : " << exp << '\n';
    }

    cout << "! " << *vals.begin() << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}