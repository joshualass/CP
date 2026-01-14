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

const int mod = 998244353;

struct Fenwick {
    vector<ll> fen; 
    int n;
    
    Fenwick(int n): n(n) {
        fen.resize(n + 1);
    }

    void update(int p, ll val) {
        for (int i = p; i <= n; i += i & -i) fen[i] = (fen[i] + val) % mod;
    }

    ll get(int p) {
        ll ans = 0;
        for (int i = p; i; i -= i & -i) ans = (ans + fen[i]) % mod;
        return ans;
    }
};




signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>> (n + 1, vector<ll> (n + 1)));
    vector<vector<ll>> dp2(n + 1, vector<ll> (n + 1)); // dp2[l, r] = sum dp[l, r, k] l < l <= k

    vector<vector<ll>> a(n + 1, vector<ll> (n + 1));

    for (int l = 1; l <= n; l++) {
        a[l][l] = 1;
        for (int r = l + 1; r <= n; r++) {
            a[l][r] = a[l][r - 1];
            if (v[r] > v[l]) a[l][r] = a[l][r] * 2 % mod;

        }
    }



    vector<vector<vector<ll>>> ds(n + 1, vector<vector<ll>> (n + 1, vector<ll>(n + 1)));

    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (len == 1) {
                dp2[l][r] = 1;
                continue;
            }
            dp[l][r][l + 1] = dp2[l + 1][r] * a[l + 1][r] % mod;
            ds[l][r][v[l + 1]] = dp[l][r][l + 1];
            dp2[l][r] = (dp2[l][r] + dp[l][r][l + 1]) % mod;
            for (int k = l + 2; k <= r; k++) {
                ll tmp = ds[l][k - 1][v[k] - 1];
                dp[l][r][k] = tmp * a[k][r] % mod * dp2[k][r] % mod;
                ds[l][r][v[k]] = dp[l][r][k];
                dp2[l][r] = (dp2[l][r] + dp[l][r][k]) % mod;
            }   

            for (int val = 1; val <= n; val++) ds[l][r][val] = (ds[l][r][val] + ds[l][r][val - 1]) % mod;
        }
    }


    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cout << a[i][j] << " ";
    //     }
    //     cout << '\n';
    // }

    // for (int i = 2; i <= n; i++) cout << dp[1][n][i] << " ";
    // cout << '\n';

    // cout << "----\n";

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cout << dp2[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    cout << dp2[1][n] << '\n';


    return 0;
}
