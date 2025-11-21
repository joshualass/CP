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

const int SN = 445;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
    }

    int l = 0, r = 0;
    ll sum = 0;

    //adding to sum, a[idx]
    auto insert = [&](int idx) -> void {
        sum += a[idx];
    };

    //remove from sum, a[idx]
    auto erase = [&](int idx) -> void {
        sum -= a[idx];
    };

    vector<array<int,3>> queries; // {l, r, query_id}
    for(int qq = 0; qq < q; qq++) {
        int a, b; cin >> a >> b;
        a--;
        queries.push_back({a, b, qq}); 
    }

    

    sort(queries.begin(), queries.end(), [&](const auto &lhs, const auto &rhs) -> bool {

        int lhs_lbucket = lhs[0] / SN;
        int lhs_rbucket = lhs[1] / SN;

        int rhs_lbucket = rhs[0] / SN;
        int rhs_rbucket = rhs[1] / SN;

        //first compare the row they are in
        if(lhs_lbucket != rhs_lbucket) {
            return lhs_lbucket < rhs_lbucket;
        }

        return (lhs[1] < rhs[1]) ^ lhs_lbucket % 2;

        // if(lhs_lbucket % 2 == 0) {
        //     return lhs[1] < rhs[1];
        // } else {
        //     return lhs_rbucket > rhs_rbucket;
        // }
    });

    vector<ll> res(q);
    for(auto [a, b, query_id] : queries) {
        while(r < b) {
            insert(r);
            r++;
        }
        //expand the left pointer
        while(l > a) {
            l--;
            insert(l);
        }
        //shrink the right pointer until it is the same size
        while(r > b) {
            r--;
            erase(r);
        }
        //shrink the left pointer until it is the same size
        while(l < a) {
            erase(l);
            l++;
        }
        // cout << "l : " << l << " r : " << r << endl;
        // cout << sum << '\n';
        res[query_id] = sum;
    }

    for(int i = 0; i < q; i++) cout << res[i] << '\n';

    // for(int qq = 0; qq < q; qq++) {
    //     int a, b; cin >> a >> b;
    //     //[a, b)
    //     a--;
    //     //make query 0 indexed and left inclusive, right exclusive
    //     //move the right pointer to the right
    //     while(r < b) {
    //         insert(r);
    //         r++;
    //     }
    //     //expand the left pointer
    //     while(l > a) {
    //         l--;
    //         insert(l);
    //     }
    //     //shrink the right pointer until it is the same size
    //     while(r > b) {
    //         r--;
    //         erase(r);
    //     }
    //     //shrink the left pointer until it is the same size
    //     while(l < a) {
    //         erase(l);
    //         l++;
    //     }
    //     // cout << "l : " << l << " r : " << r << endl;
    //     cout << sum << '\n';
    // }

    return 0;
}
