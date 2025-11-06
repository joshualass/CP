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
typedef vector<int> vi;
typedef vector<ll> vl;

struct FT {
    int n;
    int* t;

    FT(int n) {
        this->n = n;
        t = new int[n + 1];
        for(int i = 0; i < n + 1; i++) t[i] = 0;
    }

    //inserts element at ind
    void add(int ind, int val) {
        ind ++;
        for(int i = ind; i <= n; i += i & (-i)) {
            t[i] += val;
        }
    }

    //number of elements in range [0, ind)
    int get(int ind) {
        int ans = 0;
        for(int i = ind; i > 0; i -= i & (-i)) {
            ans += t[i];
        }
        return ans;
    }
};

vi gen_perm(int n) {
    vi p(n);
    for(int i = 0; i < n; i++) p[i] = i;
    shuffle(p.begin(), p.end(), mt19937(time(0)));
    return p;
}

void solve(int n) {
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    // a = gen_perm(n);
    // for(int i = 0; i < n; i++) cout << a[i] << " ";
    // cout << "\n";
    {
        set<int> s;
        for(int i = 0; i < n; i++) s.insert(a[i]);
        map<int, int> m;
        int indptr = 0;
        for(auto i = s.begin(); i != s.end(); i++) {
            m[*i] = indptr ++;
        }
        assert(indptr == n);
        for(int i = 0; i < n; i++) {
            a[i] = m[a[i]];
        }
    }
    FT ft(n);
    for(int i = 0; i < n; i++) {
        ft.add(i, 1);
    }
    vector<pair<int, int>> ord; //{val, ind}
    for(int i = 0; i < n; i++) {
        ord.push_back({a[i], i});
    }
    sort(ord.begin(), ord.end());
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        // for(int j = 0; j < n; j++) cout << ft.get(j + 1) - ft.get(j) << " ";
        // cout << "\n";
        // cout << "ORD : " << ord[i].first << " " << ord[i].second << "\n";
        int cpos = ord[i].second;
        int l = ft.get(cpos);
        int r = n - i - 1 - l;
        ans += min(l, r);
        // cout << "LR : " << l << " " << r << " " << cpos << "\n";
        ft.add(cpos, -1);
    }
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    solve(n);
    // while(1) {
    //     solve(n);
    // }

    return 0;
}
