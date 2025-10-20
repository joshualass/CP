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

const ll mod = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<char, int> vmp, cmp;
    int vindptr = 0, cindptr = 0;
    {
        for(char i = 'a'; i <= 'z'; i++) {
            if(i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u') {
                vmp[i] = vindptr ++;
            }
            else cmp[i] = cindptr ++;
        }
        for(char i = 'A'; i <= 'Z'; i++) {
            if(i == 'A' || i == 'E' || i == 'I' || i == 'O' || i == 'U') {
                vmp[i] = vindptr ++;
            }
            else cmp[i] = cindptr ++;
        }
    }
    string s;
    cin >> s;
    int n = s.size();
    vector<int> v(n, -1), c(n, -1);
    for(int i = 0; i < n; i++) {
        if(vmp.count(s[i])) v[i] = vmp[s[i]];
        else c[i] = cmp[s[i]];
    }
    vector pfx(n + 1, vector(vindptr, vector<ll>(cindptr, 0)));
    vector sfx(n + 1, vector(vindptr, vector<ll>(cindptr, 0)));
    {
        vector<ll> vcnt(vindptr, 0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < vindptr; j++) for(int k = 0; k < cindptr; k++) {
                pfx[i + 1][j][k] = pfx[i][j][k];
            }
            if(v[i] != -1) {
                vcnt[v[i]] ++;
            }
            else {
                for(int j = 0; j < vindptr; j++) {
                    pfx[i + 1][j][c[i]] += vcnt[j];
                }
            }
        }
    }
    {
        vector<ll> vcnt(vindptr, 0);
        for(int i = n - 1; i >= 0; i--) {
            for(int j = 0; j < vindptr; j++) for(int k = 0; k < cindptr; k++) {
                sfx[i][j][k] = sfx[i + 1][j][k];
            }
            if(v[i] != -1) {
                vcnt[v[i]] ++;
            }
            else {
                for(int j = 0; j < vindptr; j++) {
                    sfx[i][j][c[i]] += vcnt[j];
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        if(v[i] == -1) continue;
        {
            ll psum = 0, ssum = 0;
            for(int j = 0; j < vindptr; j++) for(int k = 0; k < cindptr; k++) {
                if(j == v[i]) continue;
                psum += pfx[i][j][k], ssum += sfx[i][j][k];
            }
            psum %= mod;
            ssum %= mod;
            ans = (ans + (psum * ssum) % mod) % mod;
        }
        for(int j = 0; j < vindptr; j++) {
            ll psum = 0, ssum = 0;
            for(int k = 0; k < cindptr; k++) {
                if(j == v[i]) continue;
                psum += pfx[i][j][k], ssum += sfx[i][j][k];
            }
            psum %= mod;
            ssum %= mod;
            ans -= (psum * ssum) % mod;
            while(ans < 0) ans += mod;
        }
        for(int k = 0; k < cindptr; k++) {
            ll psum = 0, ssum = 0;
            for(int j = 0; j < vindptr; j++) {
                if(j == v[i]) continue;
                psum += pfx[i][j][k], ssum += sfx[i][j][k];
                ssum %= mod;
            }
            psum %= mod;
            ans -= (psum * ssum) % mod;
            while(ans < 0) ans += mod;
        }
        for(int j = 0; j < vindptr; j++) for(int k = 0; k < cindptr; k++) {
            if(j == v[i]) continue;
            ans = (ans + (pfx[i][j][k] * sfx[i][j][k]) % mod) % mod;
        }
        // cout << "I : " << i << " " << ans << "\n";
    }
    cout << ans << "\n";

    return 0;
}
