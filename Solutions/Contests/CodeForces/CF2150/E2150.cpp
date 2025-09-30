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

/*
does not pass all the time, but it is close. I feel like i've thought my idea thoroughly through and should step back and try another approach. still thinking about this problem. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {

    int n; cin >> n;
    int sz = n * 2 - 1;
    vector<int> a(sz);
    iota(a.begin(), a.end(), 0);

    auto interact = [&](vector<int> b, int x) -> bool {
        // ops++;
        // for(int c : b) if(hidden[c] == x) return 1;
        // return 0;
        cout << "? " << x + 1 << " " << b.size();
        for(int c : b) cout << " " << c + 1;
        cout << endl;
        int res; cin >> res;
        if(res == -1) assert(0);
        return res;
    };

    set<int> clr;
    auto chop = [&](auto self, int l, int r, int x) -> bool {
        // cout << "l : " << l << " r : " << r << endl;
        if(l + 1 == r) {
            return 1;
            clr.insert(l);
        }
        int mid = (l + r + 1) / 2;
        vector<int> lhs(a.begin() + l, a.begin() + mid);
        vector<int> rhs(a.begin() + mid, a.begin() + r);
        int lval = interact(lhs, x);
        // cout << "lval ? : " << lval << endl;
        if(lval == 0) {
            return self(self, mid, r, x);
        }
        int rval = interact(rhs, x);
        if(rval) {
            return 0;
        }
        return self(self, l, mid, x);
    };

    // int n = (sz + 1) / 2;
    vector<int> cand(n);
    iota(cand.begin(), cand.end(), 0);
    shuffle(cand.begin(), cand.end(), rng);

    for(int i = 0; i < n; i++) {
        shuffle(a.begin(), a.end(), rng);
        if(chop(chop, 0, a.size(), cand[i])) {
            cout << "! " << cand[i] + 1 << endl;
            return;
        }
        for(int j = ((int) a.size()) - 1; j >= 0; j--) {
            if(clr.count(j)) {
                a.erase(a.begin() + j);
            }
        }
        clr.clear();
    }

}

int estimate_ops(int debug, vector<int> hidden) {

    // cout << "hidden : " << hidden << '\n';
    int n, sz;

    if(!debug) {
        cin >> n;
        sz = n * 2 - 1;
    } else {
        sz =
        hidden.size();
    }

    vector<int> a(sz);
    iota(a.begin(), a.end(), 0);
    shuffle(a.begin(), a.end(), rng);

    int ops = 0;

    map<array<int,2>, int> accounted;
    auto interact = [&](vector<int> b, int x) -> bool {
        ops++;
        for(int c : b) if(hidden[c] == x) return 1;
        return 0;
    };

    auto chop = [&](auto self, int l, int r, int x) -> bool {
        //when called on range [l, r], we expect that there are 2 of this element in this range. 
        if(l + 1 == r) {
            return 1;
        }

        int mid = (l + r) / 2;

        //case one of the sides is full, so we don't need to do any operations
        if(accounted[{l,mid}] == mid - l) {
            accounted[{mid, r}] += 2;
            return self(self, mid, r, x);
        }

        if(accounted[{mid, r}] == r - mid) {
            accounted[{l, mid}] += 2;
            return self(self, l, mid, x);
        }

        int rem_lhs = (mid - l) - accounted[{l, mid}];
        int rem_rhs = (r - mid) - accounted[{mid, r}];

        vector<int> first(a.begin() + l, a.begin() + mid), second(a.begin() + mid, a.begin() + r);
        array<int,2> first_r = {l, mid}, second_r = {mid, r};

        if(rem_lhs > rem_rhs) {
            swap(first, second);
            swap(first_r, second_r);
        }

        int first_val = interact(first, x);
        accounted[first_r] += first_val;

        //try to avoid as many of these cases as possible
        if(first_val == 0) {
            accounted[second_r] += 2;
            return self(self, second_r[0], second_r[1], x);
        }

        int second_val = interact(second, x);
        accounted[second_r] += second_val;

        if(second_val) {
            return 0;
        }

        //try to avoid as many of these cases as possible
        accounted[first_r]++;
        return self(self, first_r[0], first_r[1], x);
    };

    n = (sz + 1) / 2;

    vector<int> cand(n - 1);
    iota(cand.begin(), cand.end(), 0);
    shuffle(cand.begin(), cand.end(), rng);
    cand.push_back(n - 1);

    // vector<int> cand(n);
    // iota(cand.begin(), cand.end(), 0);
    // shuffle(cand.begin(), cand.end(), rng);

    for(int i = 0; i < n; i++) {
        // shuffle(a.begin(), a.end(), rng);
        if(chop(chop, 0, a.size(), cand[i])) {
            if(cand[i] != n - 1) {
                cout << "i : " << i << endl;
                cout << "a : " << a << endl;
                cout << "hidden : " << hidden << endl;
                cout << "cand : " << cand << endl;;
                cout << "accounted : " << accounted << endl;
                assert(cand[i] == n - 1);
            }
            // cout << "cand found : " << cand[i] << '\n';
            return ops;
        }
        for(auto [k, v] : accounted) {
            if(!(k[1] - k[0] >= v)) {
                cout << "i : " << i << endl;
                cout << "hidden : " << hidden << endl;
                cout << "cand : " << cand << endl;;
                cout << "accounted : " << accounted << endl;
                assert(k[1] - k[0] >= v);
            }

            //sanity check, is wayy too sane. 
            // int cnt = 0;
            // for(int j = 0; j <= i; j++) {
            //     for(int l = k[0]; l < k[1]; l++) {
            //         if(hidden[l] == cand[j]) cnt++;
            //     }
            // }
            // if(cnt != v) {
            //     cout << "k : " << k << " v : " << v << " cnt got : " << cnt << endl;
            //     cout << "i : " << i << endl;
            //     cout << "hidden : " << hidden << endl;
            //     cout << "cand : " << cand << endl;;
            //     cout << "accounted : " << accounted << endl;
            //     assert(0);
            // }
        }
    }

    assert(0);

}

int total_tests = 0, bad_cnt = 0;

void test(int n, int strict) {
    vector<int> a(n * 2 - 1);
    iota(a.begin(), a.begin() + n, 0);
    iota(a.begin() + n, a.end(), 0);
    shuffle(a.begin(), a.end(), rng);

    int target = n * 4 + 2 * (31 - __builtin_clz(n - 1));
    int actual = estimate_ops(1, a);

    // cout << "n : " << n << " target : " << target << " actual ops : " << actual << '\n';

    if(strict) {
        assert(actual <= target);
    }

    total_tests++;
    if(actual > target) bad_cnt++;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 1; i <= 300; i++) test(i, 0);
    // for(int i = 1; i <= 300; i++) test(i, 1);
    // for(int j = 0; j < 10; j++) for(int i = 1; i <= 300; i++) test(i, 0);

    for(int i = 1; i <= 300; i++) {
        bad_cnt = 0;
        total_tests = 0;
        for(int j = 1; i * j <= 5000; j++) test(i, 0);
        if(bad_cnt) cout << "i : " << i << " bad_cnt : " << bad_cnt << " total_tests : " << total_tests << '\n';
    }

    // for(int i = 0; i < 50; i++) test(300, 0);

    // cout << "bad : " << bad_cnt << " total : " << total_tests << '\n';

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    return 0;
}