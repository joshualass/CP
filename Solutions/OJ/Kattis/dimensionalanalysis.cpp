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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// const vector<ll> modl = {(ll) 1e9 + 7, 998244353, (ll) 1e9 + 9};
// const vector<ll> modl = {(ll) 1e9 + 9};

vector<ll> modl;

ll get_random_mod() {
    ll num = rng() % ((ll)9e8);
    num += 1e8;

    while(1) {
        int ok = 1;
        for(int i = 2; i <= sqrt(num); i++) {
            if(num % i == 0) {
                ok = 0;
                break;
            }
        }
        if(ok) return num;
        num = rng() % ((ll)9e8);
        num += 1e8;
    }
}

//returns a^b % mod
ll pow(ll a, ll b, ll mod) {
    ll ans = 1, pow = a;
    while(b != 0) {
        if(b % 2) ans = (ans * pow) % mod;
        pow = (pow * pow) % mod;
        b /= 2;
    }
    return ans;
}

ll modinv(ll a, ll mod) {
    // cout << "MODINV : " << a << " " << mod << endl;
    return pow(a, mod - 2, mod);
}

vector<bool> do_gaussian(vector<vector<ll>> mat, ll mod) {
    int n = mat.size();
    int indptr = mat[0].size();
    vector<bool> v(n, false);
    for(int i = 0; i < indptr; i++) {
        int r = -1;
        for(int j = 0; j < n; j++) {
            if(v[j]) continue;
            if(mat[j][i] == 0) continue;
            r = j;
            break;
        }
        if(r == -1) continue;
        v[r] = true;
        ll vinv = modinv(mat[r][i], mod);
        // cout << "R : " << r << " " << vinv << "\n";
        for(int j = 0; j < n; j++) {
            if(j == r) continue;
            ll mult = (mat[j][i] * vinv) % mod;
            for(int k = 0; k < indptr; k++) {
                mat[j][k] -= (mat[r][k] * mult) % mod;
                while(mat[j][k] < 0) mat[j][k] += mod;
            }
        }
        // cout << "MAT : \n";
        // for(int i = 0; i < n; i++) {
        //     for(int j = 0; j < indptr; j++) cout << mat[i][j] << " ";
        //     cout << "\n";
        // }
    }
    bool is_valid = true;
    vector<bool> bad(indptr, false);
    for(int i = 0; i < n; i++) {
        int nzcnt = 0;
        int nzind = -1;
        for(int j = 0; j < indptr; j++) {
            if(mat[i][j] != 0) {
                nzcnt ++;
                nzind = j;
            }
        }
        if(nzcnt == 1) {
            is_valid = false;
            bad[nzind] = true;
        }
    }
    return bad;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 5; i++) modl.push_back(get_random_mod());

    int n;
    cin >> n;
    {
        string tmp;
        getline(cin, tmp);
    }
    map<string, int> mp;
    int indptr = 0;
    vector<vector<string>> eqn;
    for(int i = 0; i < n; i++) {
        vector<string> eq;
        string line;
        getline(cin, line);
        for(int j = 0; j < line.size();) {
            int r = j;
            while(r != line.size() && line[r] != ' ') r ++;
            eq.push_back(line.substr(j, r - j));
            j = r + 1;
        }
        for(int j = 0; j < eq.size(); j += 2) {
            if(!mp.count(eq[j])) {
                mp[eq[j]] = indptr ++;
            }
        }
        eqn.push_back(eq);
    }  
    // cout << "DONE READING" << endl;
    // cout << "MAT : " << endl;
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < indptr; j++) {
    //         cout << mat[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    vector<bool> bad(indptr, true);
    for(int mptr = 0; mptr < modl.size(); mptr++) {
        ll mod = modl[mptr];
        vector<vector<ll>> mat(n, vector<ll>(indptr, 0));
        for(int i = 0; i < n; i++) {
            bool aft_eq = false;
            bool neg = false;
            for(int j = 0; j < eqn[i].size(); j++) {
                // cout << "EQN : " << eqn[i][j] << endl;
                if(j % 2 == 0) {
                    if(eqn[i][j] == "1") {
                        //do nothing
                    }
                    else {
                        //variable
                        assert(mp.count(eqn[i][j]));
                        int ind = mp[eqn[i][j]];
                        bool is_neg = aft_eq ^ neg;
                        mat[i][ind] += (is_neg? -1 : 1);
                        if(mat[i][ind] < 0) mat[i][ind] += mod;
                    }
                }
                else {
                    if(eqn[i][j] == "=") {
                        aft_eq = true;
                        neg = false;
                    }
                    else if(eqn[i][j] == "*") {
                        neg = false;
                    }
                    else if(eqn[i][j] == "/") {
                        neg = true;
                    }
                    else assert(false);
                }
            }
        }
        vector<bool> nxt = do_gaussian(mat, mod);
        // cout << "NXT : ";
        // for(int i = 0; i < indptr; i++) cout << nxt[i] << " ";
        // cout << "\n";
        for(int j = 0; j < indptr; j++) bad[j] = bad[j] && nxt[j];
    }
    bool is_valid = true;
    for(int i = 0; i < indptr; i++) if(bad[i]) is_valid = false;
    cout << (is_valid? "valid" : "invalid") << "\n";


    return 0;
}
