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
Pacific Northwest Regional 2025
B. Bus Seating
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k, m, c; cin >> n >> k >> m >> c;
    map<int,set<int>> avail;

    for(int i = 0; i < n; i++) avail[0].insert(i);

    for(int i = 0; i < m; i++) {
        int row; cin >> row;
        row--;

        int best_row = -1;
        ll best_shift = 0;

        auto comp = [&](int try_row, int try_shift) -> void {
            if(best_row == -1) {
                best_row = try_row;
                best_shift = try_shift;
            } else {
                //try_shift >= best_shift. 
                try_shift -= best_shift;

                ll cur = c - abs(row - best_row);
                ll test = c - abs(row - try_row);

                if(try_shift >= 31) return;
                for(int i = 0; i < try_shift; i++) cur <<= 1;
                if(test > cur || test == cur && try_row < best_row) {
                    best_row = try_row;
                    best_shift = try_shift + best_shift;
                }

            }
        };

        auto it = avail.begin();

        for(int j = 0; j < 32; j++) {
            if(it == avail.end()) break;

            auto later = it->second.lower_bound(row);
            if(later != it->second.end()) {
                comp(*later, it->first);
            }
            auto earlier = it->second.lower_bound(row);
            if(earlier != it->second.begin()) {
                earlier--;
                comp(*earlier, it->first);
            }
            it++;
        }

        cout << best_row + 1 << " \n"[i == m - 1];
        avail[best_shift].erase(best_row);
        if(avail[best_shift].empty()) avail.erase(best_shift);

        if(best_shift + 1 < k) avail[best_shift + 1].insert(best_row);
        
        // cout << "i : " << i << " best row : " << best_row << " bs : " << best_shift << '\n';
        // cout << "printing avail .......\n";
        // for(auto [k, v] : avail) {
        //     cout << "k : " << k << " indices here : ";
        //     for(int x : v) cout << x << " ";
        //     cout << '\n';
        // }

    }



    return 0;
}
