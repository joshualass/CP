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

    vector<ll> nums;


    for(ll i = 1; i < 1 << 10; i++) {
        vector<ll> a;
        for(ll j = 0; j < 10; j++) {
            if((i >> j) & 1) a.push_back(j);
        }

        while(1) {
            ll num = 0;
            for(ll x : a) {
                num *= 10;
                num += x;
            }
            nums.push_back(num);
            if(!next_permutation(a.begin(), a.end())) break;
        }
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    string s; cin >> s;
    vector<ll> queries;
    
    string cur = "";
    for(char c : s) {
        if(c == '-' || c == ',') {
            try {
                queries.push_back(stoll(cur));
            } catch(...) {
                cout << "bad for cur : " << cur << endl;
            }
            cur = "";
        } else {
            cur.push_back(c);
        }
    }

    queries.push_back(stoll(cur));

    ll res = 0;
    for(ll i = 0; i < queries.size(); i += 2) {
        // ll lo = queries[i], hi = queries[i + 1];
        // ll good_cnt = distance(lower_bound(nums.begin(), nums.end(), lo), upper_bound(nums.begin(), nums.end(), hi));
        // ll contrib = (hi - lo + 1) - good_cnt;
        // cout << "lo : " << lo << " hi : " << hi << " contrib : " << contrib << endl;
        // res += contrib;
        for(ll j = queries[i]; j <= queries[i + 1]; j++) {
            int ok = 1;
            string s = to_string(j);
            if(s.size() % 2 == 0) {
                string lhs = s.substr(0, s.size() / 2), rhs = s.substr(s.size() / 2);
                if(lhs == rhs) ok = 0;
            }
            for(char c = '0'; c <= '9'; c++) {
                if(count(s.begin(), s.end(), c) > 1) ok = 0;
            }
            if(ok) res += j;
        }
    }

    cout << res << '\n';

    return 0;
}
