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

const ll mod = 998244353;

ll pow(ll a, ll b) {
    ll res = 1, p = a;
    while(b != 0) {
        if(b % 2) res = (res * p) % mod;
        p = (p * p) % mod;
        b /= 2;
    }
    return res;
}

ll inv(ll a) {
    return pow(a, mod - 2);
}

int n, m;
vl a, b;

vl solve_fast() {
    vl U(n, 1);    //U[i] = probability of card i being discarded
    for(int i = 0; i < n; i++) {
        if(b[i] != -1) {
            U[i] = 0;
        }
        else {
            for(int j = i - 1; j >= 0; j--) { 
                if((a[j] % a[i]) == 0 && U[j] == 0) U[i] = 0;
            }
        }
    }
    // cout << "A : ";
    // for(int i = 0; i < n; i++) cout << a[i] << " ";
    // cout << "\n";
    // cout << "U : ";
    // for(int i = 0; i < n; i++) cout << U[i] << " ";
    // cout << "\n";
    //E[i][j] = probability of jth person getting ith card
    vector<vl> E(n, vl(m, -1));
    for(int i = 0; i < n; i++) {
        if(b[i] != -1) {
            for(int j = 0; j < m; j++) E[i][j] = 0;
            E[i][b[i]] = 1;
        }
        else if(U[i] == 1) {
            for(int j = 0; j < m; j++) E[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(E[i][j] != -1) continue;
            E[i][j] = 0;
            ll cnt = 0;
            for(int k = i - 1; k >= 0; k--) {
                if(a[k] % a[i]) continue;   //a[k] not a multiple of a[i]
                if(U[k] == 1) continue; //always discarded, doesn't matter
                if(b[k] != -1) {
                    if(b[k] == j) {
                        E[i][j] = (E[i][j] + inv(cnt + 1)) % mod;
                    }
                    break;
                }
                else {
                    ll p = E[k][j];
                    ll inner = (inv(cnt + 1) * inv(cnt + 2)) % mod;
                    // cout << "INNER : " << inner << " " << cnt << endl;
                    E[i][j] = (E[i][j] + p * inner) % mod;
                    cnt ++;
                }
            }
        }
    }
    // cout << "E : \n";
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) cout << E[i][j] << " ";
    //     cout << "\n";
    // }
    vl ans(m);
    for(int i = 0; i < m; i++) {
        ans[i] = 0;
        for(int j = 0; j < n; j++) ans[i] = (ans[i] + E[j][i]) % mod;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << "INV2 : " << inv(2) << endl;
    // cout << "INV^ : " << inv(6) << endl;
    cin >> n >> m;
    a = vl(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    reverse(a.begin(), a.end());
    b = vl(n);
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        b[i] --;
    }
    reverse(b.begin(), b.end());
    vl ans = solve_fast();
    for(int i = 0; i < m; i++) cout << ans[i] << " ";
    cout << "\n";

    return 0;
}
