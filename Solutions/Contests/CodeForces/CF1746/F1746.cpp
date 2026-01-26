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
#include <immintrin.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#pragma GCC target("avx2")


/*
first idea was kind of blasting off, trying multiplication mod, but there are too many cases where k is coprime to each of 
primes - 1 ...

still getting wa / tle ... 

bad idea. cheese with SIMD, GGGG. 

*/

const int t = 20;
const int MAXN = 300000;
ll F[MAXN][t];
int b[t][MAXN * 2];

const int m = 6;
__m128i bf[m][MAXN * 2];
__m128i ff[m][MAXN];


ll sum(int z, int r) {
    r --; ll ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += F[r][z];
    return ret;
}

ll sum(int z, int l, int r) {
    return sum(z, r) - sum(z, l);
}

void add(int z, int ind, int val) {
    for (; ind < MAXN; ind = ind | (ind + 1)) F[ind][z] += val;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    set<int> s(a.begin(), a.end());

    vector<vector<int>> queries;
    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            int i, x; cin >> i >> x;
            i--;
            queries.push_back({i, x});
            s.insert(x);
        } else {
            int l, r, k; cin >> l >> r >> k;
            l--;
            queries.push_back({l, r, k});
        }
    }

    map<int,int> cm;
    int p = 0;
    for(int x : s) cm[x] = p++;

    const int MOD = 1000000000 / 300000;

    for(int i = 0; i < n; i++) a[i] = cm[a[i]];
    
    // for(int i = 0; i < t; i++) {
    //     for(int j = 0; j < p; j++) b[i][j] = rng() % MOD;
    //     for(int j = 0; j < n; j++) {
    //         add(i, j, b[i][a[j]]);

    //     }
    // }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < p; j++) {
            int v0 = rng() % MOD, v1 = rng() % MOD, v2 = rng() % MOD, v3 = rng() % MOD;
            bf[i][j] = _mm_set_epi32(v0, v1, v2, v3);
        }
        for(int j = 0; j < n; j++) {
            int ind = j;
            for (; ind < n; ind = ind | (ind + 1)) ff[i][ind] = _mm_add_epi32(ff[i][ind], bf[i][a[j]]);
        }
    }
    
    // cout << "printing starting bf" << endl;
    // for(int i = 0; i < m; i++) {
    //     for(int j = 0; j < p; j++) {
    //         cout << "i : " << i << " j : " << j << " v0 : " << _mm_extract_epi32(bf[i][j], 0) << " v1 : " << _mm_extract_epi32(bf[i][j], 1) << " v2 : " << _mm_extract_epi32(bf[i][j], 2) << " v3 : " << _mm_extract_epi32(bf[i][j], 0) << endl;
    //     }
    // }
    
    // cout << "printing starting ff" << endl;
    // for(int i = 0; i < m; i++) {
    //     for(int j = 0; j < n; j++) {
    //         cout << "i : " << i << " j : " << j << " v0 : " << _mm_extract_epi32(ff[i][j], 0) << " v1 : " << _mm_extract_epi32(ff[i][j], 1) << " v2 : " << _mm_extract_epi32(ff[i][j], 2) << " v3 : " << _mm_extract_epi32(ff[i][j], 0) << endl;
    //     }
    // }

    for(auto query : queries) {
        if(query.size() == 2) {
            int i = query[0], x = query[1];
            x = cm[x];
            // for(int j = 0; j < t; j++) {
            //     // trees[j].add(i, -b[j][a[i]]);
            //     // trees[j].add(i, b[j][x]);

            //     // trees[j].add(i, -b[j][a[i]]);
            //     // trees[j].add(i, b[j][x] - b[j][a[i]]);

            //     add(j, i, b[j][x] - b[j][a[i]]);

            //     // treess[j].update(i, -b[j][a[i]]);
            //     // treess[j].update(i, b[j][x]);
            // }
            for(int j = 0; j < m; j++) {
                __m128i add = _mm_sub_epi32(bf[j][x], bf[j][a[i]]);
                int ind = i;
                for (; ind < n; ind = ind | (ind + 1)) ff[j][ind] = _mm_add_epi32(ff[j][ind], add);
            }
            
            a[i] = x;
        } else {
            int l = query[0], r = query[1], k = query[2];
            int ok = 1;
            // for(int j = 0; j < t; j++) {
            //     // ll sum = trees[j].sum(l, r);
            //     ll test = sum(j, l, r);
            //     // ll sums = treess[j].query(l, r);
            //     if(test % k) ok = 0;
            //     // cout << "sum : " << sum << endl;
            //     // cout << "sums : " << sums << endl;
            // }
            
            // cout << "query l : " << l << " r : " << r << " k : " << k << endl;
            
            for(int j = 0; j < m; j++) {
                __m128i res = _mm_setzero_si128();
                int cur = r - 1;
                for (; cur >= 0; cur = (cur & (cur + 1)) - 1) res = _mm_add_epi32(res, ff[j][cur]);
                cur = l - 1;
                for (; cur >= 0; cur = (cur & (cur + 1)) - 1) res = _mm_sub_epi32(res, ff[j][cur]);
                if(_mm_extract_epi32(res, 0) % k) {
                    // cout << "v0 : " << _mm_extract_epi32(res, 0) << endl;
                    ok = 0;
                }
                if(_mm_extract_epi32(res, 1) % k) {
                    // cout << "v1 : " << _mm_extract_epi32(res, 1) << endl;
                    ok = 0;
                }
                if(_mm_extract_epi32(res, 2) % k) {
                    // cout << "v2 : " << _mm_extract_epi32(res, 2) << endl;
                    ok = 0;
                }
                if(_mm_extract_epi32(res, 3) % k) {
                    // cout << "v3 : " << _mm_extract_epi32(res, 3) << endl;
                    ok = 0;
                }
            }
            cout << (ok ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}