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
typedef int64_t ll;
typedef long double ld;
using namespace std;

const ll mod = 998244353;

const int N = 1e4;
const int H = 1;
const ll hm = (ll) 1e9 + 7;
const ll hp = 67;
vector<ll> hpp, hpinv;

ll pow(ll a, ll b, ll m) {
    ll ans = 1, pow = a;
    while(b != 0) {
        if(b % 2) {
            ans = (ans * pow) % m;
        }
        pow = (pow * pow) % m;
        b /= 2;
    }
    return ans;
}   

ll inv(ll a, ll m) {
    return pow(a, m - 2, m);
}

vector<ll> calc_hash(string& s) {
    vector<ll> h(s.size() + 1, 0);
    for(int j = 0; j < s.size(); j++) {
        h[j + 1] = (s[j] * hpp[j]) % hm;
    }
    for(int j = 1; j <= s.size(); j++) {
        h[j] = (h[j - 1] + h[j]) % hm;
    }
    return h;
}

bool is_eq(vector<ll>& h1, vector<ll>& h2, int l1, int l2, int len) {
        ll s1 = h1[l1 + len] - h1[l1];
        ll s2 = h2[l2 + len] - h2[l2];
        if(s1 < 0) s1 += hm;
        if(s2 < 0) s2 += hm;
        s1 = (s1 * hpinv[l1]) % hm;
        s2 = (s2 * hpinv[l2]) % hm;
        if(s1 != s2) {
            // cout << "INV : " << hpinv[i][l1] << "\n";
            // cout << "NEQ : " << s1 << " " << s2 << " " << (h1[i][l1 + len] - h1[i][l1]) << " " << (h2[i][l2 + len] - h2[i][l2]) << "\n";
            return false;
        }
    return true;
}

void print_h(vector<vector<ll>> &h) {
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < h[i].size(); j++) cout << h[i][j] << " ";
        cout << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    hpp = vector<ll>(N + 1), hpinv = vector<ll>(N + 1);
    hpp[0] = 1, hpinv[0] = 1;
    {
        ll p = hp, pinv = inv(p, hm);
        for(int i = 1; i <= N; i++) {
            hpp[i] = (hpp[i - 1] * p) % hm;
            hpinv[i] = (hpinv[i - 1] * pinv) % hm;
        }
    }

    string t;
    cin >> t;
    int n;
    cin >> n;
    int m = t.size();
    vector<ll> th = calc_hash(t);
    // print_h(th);
    vector<vector<ll>> c(m + 1, vector<ll>(m + 1, 0));
    vector<ll> dp(m + 1, 0);
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<ll> sh = calc_hash(s);
        // print_h(sh);
        // cout << "START : " << (-((int) t.size() - 1)) << " " << s.size() << "\n";
        for(int j = -((int) t.size() - 1); j < (int) s.size(); j++) {
            int tl = max(0, -j), sl = max(0, j);
            int len = min((int) t.size() - tl, (int) s.size() - sl);
            // cout << "TL SL : " << tl << " " << sl << " " << len << endl;
            if(is_eq(th, sh, tl, sl, len)) {
                // cout << "IS EQ : " << tl << " " << sl << " " << len << " " << s << "\n";
                if(tl == 0) dp[len] ++;
                else c[tl][tl + len] ++;
            }
        }
    }
    for(int i = 0; i <= m; i++) {
        // cout << "BASE I : " << i << " " << dp[i] << "\n";
    }
    ll invn = inv(n, mod);
    for(int i = 1; i < m; i++) {
        for(int j = i + 1; j <= m; j++) {
            dp[j] = (dp[j] + (dp[i] * invn) % mod * c[i][j]) % mod;
        }
    }
    ll ans = (dp[m] * invn) % mod;
    cout << ans << "\n";

    return 0;
}
