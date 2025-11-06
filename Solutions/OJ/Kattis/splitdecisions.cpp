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

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
static const ll M1 = 1e9 + 9;
ll B1 = uniform_int_distribution<ll>(0, M1 - 1)(rng);

struct hstring {

    vector<long long> pow;

    vector<long long> p_hash;

    hstring(const string &s): p_hash(s.size() + 1), pow(1, 1) {
        while(pow.size() <= s.size()) { pow.push_back((pow.back() * B1) % M1);}
        p_hash[0] = 0;
        for (int i = 0; i < s.size(); i++) {
            p_hash[i + 1] = ((p_hash[i] * B1) % M1 + s[i]) % M1;
        }
    }

    long long get_hash(int start, int end) {
        long long raw_val = (p_hash[end] - (p_hash[start] * pow[end - start]));
        return (raw_val % M1 + M1) % M1;
    }
};

static const ll M2 = 1e9 + 7;
ll B2 = uniform_int_distribution<ll>(0, M2 - 1)(rng);

struct hstring2 {

    vector<long long> pow;

    vector<long long> p_hash;

    hstring2(const string &s): p_hash(s.size() + 1), pow(1, 1) {
        while(pow.size() <= s.size()) { pow.push_back((pow.back() * B2) % M2);}
        p_hash[0] = 0;
        for (int i = 0; i < s.size(); i++) {
            p_hash[i + 1] = ((p_hash[i] * B2) % M2 + s[i]) % M2;
        }
    }

    long long get_hash(int start, int end) {
        long long raw_val = (p_hash[end] - (p_hash[start] * pow[end - start]));
        return (raw_val % M2 + M2) % M2;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // string t1 = "CELL", t2 = "CELL";
    // hstring test1(t1), test2(t2);
    // cout << test1.get_hash(2, 4) << endl;
    // cout << test2.get_hash(2, 4) << endl;

    int n; cin >> n;
    vector<string> a(n);
    vector<hstring> h1;
    vector<hstring2> h2;

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        a[i] = s;
        h1.push_back(hstring(s));
        h2.push_back(hstring2(s));
    }

    // for(int i = 0; i <= a[0].size(); i++) {
    //     for(int j = i; j <= a[0].size(); j++) {
    //         cout << "i : " << i << " j : " << j << " h : " << h1[0].get_hash(i, j) << endl;
    //     }
    // }

    map<pair<array<int,2>,array<string,2>>, int> pairs;
    vector<vector<pair<array<int,2>,array<string,2>>>> b(n, vector<pair<array<int,2>,array<string,2>>>(n));

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i].size() == a[j].size()) {
                int l = 0, r = a[i].size();
                while(l != r) {
                    int m = (l + r + 1) / 2;
                    if(h1[i].get_hash(0, m) == h1[j].get_hash(0, m) && h2[i].get_hash(0, m) == h2[j].get_hash(0, m)) {
                        l = m;
                    } else {
                        r = m - 1;
                    }
                }
                // cout << "i : " << i << " j : " << j << " l : " << l << endl;
                if(l + 2 <= a[i].size() && a[i][l] != a[j][l] && a[i][l+1] != a[j][l+1]) {
                    // cout << "make it to check 2" << endl;
                    // cout << "lo : " << l + 2 << " hi : " << a[i].size() << endl;
                    // cout << "string i : " << a[i] << '\n';
                    // cout << "string j : " << a[j] << '\n';
                    // cout << "test hash0 : " << h1[i].get_hash(l + 2, a[i].size()) << endl;
                    // cout << "test hash0 : " << h1[j].get_hash(l + 2, a[i].size()) << endl;
                    if(h1[i].get_hash(l + 2, a[i].size()) == h1[j].get_hash(l + 2, a[i].size()) && h2[i].get_hash(l + 2, a[i].size()) == h2[j].get_hash(l + 2, a[i].size())) {
                        string c = a[i].substr(l, 2), d = a[j].substr(l,2);
                        b[i][j] = pair<array<int,2>,array<string,2>>{{l, ((int) a[i].size()) - (l + 2)}, {min(c,d), max(c,d)}};
                        // cout << "pair is good i : " << i << " j : " << j << " l : " << l << '\n';
                        pairs[b[i][j]]++;
                    }
                }
            }
        }
    }

    int res = 0;
    for(auto [k, v] : pairs) {
        auto [szs, strs] = k;
        // cout << "left : " << szs[0] << " right : " << szs[1] << " strup : " << strs[0] << " strdown : " << strs[1] << " cnts : " << v << endl;
        res += v == 1;
    }

    cout << res << '\n';

    return 0;
}
