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

typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

struct SuffixArray {
    vi sa, lcp;
    SuffixArray(vector<int> s, int lim = 256) {
        s.push_back(0); int n = sz(s), k = 0, a, b;
        vi x(all(s)), y(n), ws(max(n, lim));
        sa = lcp = y, iota(all(sa), 0);
        for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i,0,n) if(sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i,0,n) ws[x[i]]++;
            rep(i,1,lim) ws[i] += ws[i - 1];
            for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
            for (k && k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
    }
};

string solve(int k, int t, string s) {

    t %= k;

    // cout << "t : " << t << '\n';
    
    int bs = 1 << t;
    int os = 1 << (k - t);

    vector<int> a;
    for(int i = 0; i < os; i++) {
        for(int k = 0; k < 2; k++) {
            for(int j = 0; j < bs; j++) {
                a.push_back(s[i + j * os]);
            }
        }
    }

    // for(int x : a) cout << x << " ";
    // cout << '\n';

    SuffixArray sa(a);

    // cout << "sa\n";
    // for(int x : sa.sa) cout << x << " ";
    // cout << '\n';
    // cout << "lcp\n";
    // for(int x : sa.lcp) cout << x << ' ';

    // cout << "sa size : " << sa.sa.size() << '\n';
    // cout << "lcp size : " << sa.lcp.size() << '\n';

    vector<int> b(1 << (k + 1));
    int p = 0;
    for(int i = 1; i <= 1 << (k + 1); i++) {
        if(sa.lcp[i] < bs) p++;
        b[sa.sa[i]] = p;
    }

    // cout << "b\n";
    // for(int x : b) cout << x << " ";
    // cout << '\n';

    // cout << "c construction\n";

    vector<int> c;
    // for(int i = 0; i < bs; i++) {
    //     for(int j = 0; j < 2; j++) {
    //         for(int k = 0; k < b.size(); k += bs * 2) {
    //             // cout << i + k << " ";
    //             c.push_back(b[i + k]);
    //         }
    //     }
    // }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 1 << k; j++) {
            c.push_back(b[j % os * bs * 2 + j / os]);
        }
    }

    // cout << '\n';

    // cout << "c\n";
    // for(int x : c) cout << x << " ";
    // cout << '\n';

    SuffixArray sa2(c, 1 << (k + 1));

    // cout << "sa2 sa\n";
    // for(int x : sa2.sa) cout << x << " ";
    // cout << endl;

    int rotate = 0;

    for(int i = 1; i < sa2.sa.size(); i++) {
        int idx = sa2.sa[i];
        if(idx < 1 << k) {
            rotate = idx; 
            break;
        }
        // if(idx % (os * 2) < os) {
        //     cout << "good idx : " << idx << '\n';
        //     int x = idx % (os * 2);
        //     int y = idx / (os * 2);
        //     cout << "x : " << x << " y : " << y << '\n';
        //     // rotate = idx % (os * 2) * bs + idx / (os * 2);
        //     // rotate = y * os + x;
        //     rotate = x + y;
        //     break;
        // }
    }


    // rotate = s.size() - rotate - 1;
    // rotate = s.size() - rotate;

    // cout << "rotate : " << rotate << '\n';
    s = s.substr(rotate) + s.substr(0, rotate);

    for(int i = 0; i < t; i++) {
        string t = "";
        for(int i = 0; i * 2 < s.size(); i++) {
            t.push_back(s[i]);
            t.push_back(s[i + s.size() / 2]);
        }
        s = t;
    }

    // cout << s << endl;
    return s;
}

string solve_slow(int k, int t, string s) {

    string res(s.size(), 'z');

    for(int i = 0; i < s.size(); i++) {
        string c = s;
        c = c.substr(i) + c.substr(0, i);
        for(int j = 0; j < t; j++) {
            string nx = "";
            for(int i = 0; i * 2 < c.size(); i++) {
                nx.push_back(c[i]);
                nx.push_back(c[i + c.size() / 2]);
            }
            c = nx;
        }
        res = min(res, c);
    }
    return res;
}

void check(int k) {
    assert(k > 0);
    vector<int> a(1 << k);
    iota(a.begin(), a.end(), 0);
    vector<int> start = a;
    for(int i = 0; i < k; i++) {
        vector<int> b;
        for(int j = 0; j < 1 << (k - 1); j++) {
            b.push_back(a[j]);
            b.push_back(a[j + (1 << (k - 1))]);
        }
        a = b;
    }
    assert(a == start);
} 

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, t; cin >> k >> t;
    string s; cin >> s;
    // cout << "solve fast\n";
    cout << solve(k, t, s) << '\n';
    // cout << "solve slow\n";
    // cout << solve_slow(k, t, s) << '\n';

    // for(int k = 1; k <= 4; k++) {
    //     for(int j = 0; j < k * 100; j++) {
    //         string s = "";
    //         for(int j = 0; j < 1 << k; j++) {
    //             s.push_back(rng() % 26 + 'a');
    //         }
    //         cout << "call saul k : " << k << " t : " << j << " s : " << s << endl;
    //         string res_fast = solve(k, j, s);
    //         string res_slow = solve_slow(k, j, s);
    //         if(res_fast != res_slow) {
    //             cout << "difference in answer /!\\\n";
    //             cout << "fast res : " << res_fast << '\n';
    //             cout << "slow res : " << res_slow << '\n';
    //             assert(0);
    //         }
    //     }
    // }

    // for(int i = 1; i <= 18; i++) check(i);

    return 0;
}
