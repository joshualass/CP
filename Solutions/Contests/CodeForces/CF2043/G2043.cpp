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

/*
looked at editorial and observed the existence of O(q sqrt(n)) solution. 
otherwise, generated the solution. maybe not a clean kill, but spent a while thinking. 

very many pitfalls when implementing square root decomp and some pitfalls with overcounting some things that were only able to be discovered
by getting some WAs. 

The idea is you support an add/remove operation. Then, we consider the elements of the same value in blocks to its left and right. 
We use the p and s blocks and do some lazy range stuff
making sure not to overcount the count and do the sqrt decomp stuff correctly. 

*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// const int B = 3;
// const int N = 9;
const int B = 317;
const int N = 100000;
int cnts[N][B]; // the current count of elements of value i in blocks with index <= j
int a[N]; //the current array
int p[B][B]; //prefix sum updates, fix r, propagate l down
int s[B][B]; //suffix sum updates, fix l, propagate r up
int pie[B][B]; //PIE updates
int query_id[N], query_cnt[N];
int debug = 0;
int scramble = 1;

void clear() {
    memset(cnts,     0, sizeof(cnts));
    memset(a,        0, sizeof(a));
    memset(p,        0, sizeof(p));
    memset(s,        0, sizeof(s));
    memset(pie,      0, sizeof(pie));
    memset(query_id, 0, sizeof(query_id));
    memset(query_cnt,0, sizeof(query_cnt));
}

vector<ll> solve(int n, vector<int> arr, int q, vector<array<int,3>> queries) {
    auto get_cnt = [&](int val, int block_id) -> int {
        return cnts[val][block_id] - (block_id ? cnts[val][block_id - 1] : 0);
    };

    auto _update = [&](int idx, int val, int delta) -> void {
        if(debug) cout << "_update called idx : " << idx << " val : " << val << " delta : " << delta << endl;
        
        int block = idx / B;
        int pcnt = 0, scnt = 0;
        
        if(delta == -1) {
            for(int i = block; i < B; i++) {
                cnts[val][i] += delta;
            }
        }

        for(int i = block; i < B; i++) {
            pcnt += get_cnt(val, i);
            p[block][i] += pcnt * delta;
        }

        for(int i = block - 1; i >= 0; i--) {
            scnt += get_cnt(val, i);
            s[i][block] += scnt * delta;
        }

        // pie[block][block] -= get_cnt(val, block) * delta;

        if(delta == 1) {
            for(int i = block; i < B; i++) {
                cnts[val][i] += delta;
            }
        }
    };

    for(int i = 0; i < n; i++) {
        int x = arr[i];
        a[i] = x;
        _update(i, x, 1);
    }

    auto print_stuff = [&]() {
        cout << "cnts\n";
        for(int i = 0; i < N; i++) {
            cout << "i : " << i << " cnts[i] : ";
            for(int j = 0; j < B; j++) cout << cnts[i][j] << " \n"[j == B - 1];
        }
        cout << "a : ";
        for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
        cout << "p\n";
        for(int i = 0; i < B; i++) {
            cout << "i : " << i << " p[i] : ";
            for(int j = 0; j < B; j++) cout << p[i][j] << " \n"[j == B - 1];
        }
        cout << "s\n";
        for(int i = 0; i < B; i++) {
            cout << "i : " << i << " s[i] : ";
            for(int j = 0; j < B; j++) cout << s[i][j] << " \n"[j == B - 1];
        }
        cout << "pie\n";
        for(int i = 0; i < B; i++) {
            cout << "i : " << i << " pie[i] : ";
            for(int j = 0; j < B; j++) cout << pie[i][j] << " \n"[j == B - 1];
        }
        cout << "query_id : ";
        for(int i = 0; i < n; i++) cout << query_id[i] << " \n"[i == n - 1];
        cout << "query_cnt : ";
        for(int i = 0; i < n; i++) cout << query_cnt[i] << " \n"[i == n - 1];
    };

    if(debug) cout << "INIT PRINT\n";
    if(debug) print_stuff();

    ll last = 0;
    vector<ll> soln;

    for(int qq = 1; qq <= q; qq++) {
        int type = queries[qq - 1][0];
        assert(last >= 0);
        if(type == 1) {
            int pp = queries[qq - 1][1], xp = queries[qq - 1][2];
            int p = (scramble ? (pp + last) % n : pp);
            int x = (scramble ? (xp + last) % n : xp);
            if(debug) cout << "t1 query p : " << p << " x : " << x << endl;
            _update(p, a[p], -1);
            a[p] = x;
            _update(p, a[p], 1);
        } else {
            int lp = queries[qq - 1][1], rp = queries[qq - 1][2];
            int l = (scramble ? (lp + last) % n : lp);
            int r = (scramble ? (rp + last) % n : rp);
            if(l > r) swap(l, r);
            r++; 
            //[l, r)
            int len = r - l;

            if(debug) cout << "t2 query l : " << l << " r : " << r << endl;

            int lblock = (l + B - 1) / B; //inclusive
            int rblock = max(lblock, r / B); //exclusive

            if(debug) cout << "lblock : " << lblock << " rblock : " << rblock << endl;

            
            ll res_small = 0, res_big = 0;
            auto add_val = [&](int val) -> void {
                int add = (rblock ? cnts[val][rblock - 1] : 0);
                int sub = (lblock ? cnts[val][lblock - 1] : 0);
                int cnt = add - sub;
                if(query_id[val] == qq) {
                    cnt += query_cnt[val];
                } else {
                    query_id[val] = qq;
                    query_cnt[val] = 0;
                }

                if(debug) cout << "add val called with val : " << val << " cnt contrib : " << cnt << '\n';

                res_small += cnt;
                query_cnt[val]++;
            };

            while(l < r && l % B) add_val(a[l++]);
            while(r > l && r % B) add_val(a[--r]);

            rblock--; //now rblock is inclusive. 
            if(debug) cout << "small blocks l : " << lblock << " r : " << rblock << '\n';
            if(debug) cout << "big0 : " << res_big << endl;
            for(int i = lblock; i <= rblock; i++) {
                res_big += p[i][rblock];
            }
            if(debug) cout << "big1 : " << res_big << endl;
            for(int i = rblock; i >= lblock; i--) {
                res_big += s[lblock][i];
            }
            if(debug) cout << "big2 : " << res_big << endl;
            // if(lblock <= rblock) res_big += pie[lblock][rblock];
            if(debug) cout << "res small : " << res_small << " res big : " << res_big << endl;
            ll res = res_small + res_big;
            res = 1LL * len * (len - 1) / 2 - res;
            // cout << res << '\n';
            soln.push_back(res);
            last = res;
        }
        if(debug) cout << "info after query qq : " << qq << '\n';
        if(debug) print_stuff();
    }
    
    return soln;
}

vector<ll> solve_slow(int n, vector<int> arr, int q, vector<array<int,3>> queries) {
    vector<ll> soln;
    ll last = 0;
    for(int qq = 1; qq <= q; qq++) {
        int type = queries[qq - 1][0];
        if(type == 1) {
            int pp = queries[qq - 1][1], xp = queries[qq - 1][2];
            int p = (scramble ? (pp + last) % n : pp);
            int x = (scramble ? (xp + last) % n : xp);
            arr[p] = x;
        } else {
            int lp = queries[qq - 1][1], rp = queries[qq - 1][2];
            int l = (scramble ? (lp + last) % n : lp);
            int r = (scramble ? (rp + last) % n : rp);
            if(l > r) swap(l, r);
            r++; 
            int res = 0;
            for(int i = l; i < r; i++) {
                for(int j = i + 1; j < r; j++) {
                    if(arr[i] != arr[j]) res++;
                }
            }
            soln.push_back(res);
            last = res;
        }
    }
    return soln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    if(n) {
        vector<int> arr(n);
        for(int &x : arr) {
            cin >> x;
            x--;
        }
        int q; cin >> q;
        vector<array<int,3>> queries(q);
        for(auto &x : queries) for(auto &y : x) cin >> y;
        auto res = solve(n, arr, q, queries);
        for(auto x : res) cout << x << '\n';
    } else {
        cout << "running tests\n";
        scramble = 0;

        for(int tc = 0; tc < 1000; tc++) {
            int n = 9;
            vector<int> arr(n);
            for(int i = 0; i < 9; i++) {
                arr[i] = rng() % n;
            }
            int q = 10;
            vector<array<int,3>> queries;
            for(int i = 0; i < q; i++) {
                queries.push_back(array<int,3>{(int) (rng() % 2 + 1), (int) (rng() % n), (int) (rng() % n)});
            }
            clear();
            vector<ll> fast_soln = solve(n, arr, q, queries);
            vector<ll> slow_soln = solve_slow(n, arr, q, queries);
    
            if(fast_soln != slow_soln) {
                cout << "tc : " << tc << " BAD\n";
                cout << n << '\n';
                for(int i = 0; i < n; i++) cout << arr[i] + 1 << " \n"[i == n - 1];
                cout << q << '\n';
                for(int i = 0; i < q; i++) {
                    for(int j = 0; j < 3; j++) cout << queries[i][j] << " \n"[j == 2];
                }
                cout << "solve fast : " << fast_soln << '\n';
                cout << "solve slow : " << slow_soln << '\n';
                return 0;
            }
        }
        cout << "ALL CLEAR" << endl;
    }


    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// //even if this does not WA, it will likely later TLE as q * n^(2/3) is not intended. 

// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// const int MAXN = 100000;
// const int BS = 2000;

// int a[MAXN]; //the current array
// ll pc[MAXN / BS][MAXN / BS]; //answers computed for each interval [l, r]
// int bcp[MAXN / BS][MAXN]; //block counts prefix sum, prefix sums for how many times each value appears in the blocks
// int lq[MAXN], lqc[MAXN]; //latest query this number has been considered in, the current count that this number has appeared in
// ll tri[MAXN + 1];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     clock_t tStart = clock();

//     int n; cin >> n;
//     // int n = 100000;
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         x--;
//         // int x = rng() % n;
//         a[i] = x;
//         bcp[i / BS][x]++;
//     }

//     //compute bcp
//     for(int i = 0; i < MAXN; i++) {
//         for(int j = 1; j < MAXN / BS; j++) {
//             bcp[j][i] += bcp[j-1][i];
//         }
//     }

//     auto get_bcp = [&](int l, int r, int i) -> int {
//         return bcp[r][i] - (l ? bcp[l-1][i] : 0);
//     };

//     for(int i = 0; i <= MAXN; i++) {
//         tri[i] = 1LL * i * (i - 1) / 2;
//     }

//     for(int l = 0; l < MAXN / BS; l++) {
//         for(int r = l; r < MAXN / BS; r++) {
//             for(int i = 0; i < MAXN; i++) {
//                 pc[l][r] += tri[get_bcp(l, r, i)];
//             }
//         }
//     }

//     // int inf = 1e9;

//     //     for(int l = 0; l < MAXN / BS; l++) {
//     //         for(int r = l; r < MAXN / BS; r++) {
//     //             ll res = 0;
//     //             for(int i = l * BS; i < r * BS + BS; i++) {
//     //                 if(lq[a[i]] != inf) {
//     //                     lq[a[i]] = inf;
//     //                     lqc[a[i]] = 0;
//     //                 }
//     //                 res += lqc[a[i]]++;
//     //             }

//     //             inf++;

//     //             if(res != pc[l][r]) {
//     //                 cout << "l : " << l << " r : " << r << '\n';
//     //                 cout << "start : " << l * BS << " stop : " << r * BS + BS << '\n';
//     //                 cout << "res : " << res << '\n';
//     //                 cout << "a : ";
//     //                 for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
//     //                 cout << "pc[l][r] : " << pc[l][r] << '\n';
//     //             }

//     //             assert(res == pc[l][r]);

//     //         }
//     //     }

//     int inf = 1e9;
//     ll last = 0;
//     int q; cin >> q;
//     // int q = 300000;
//     for(int qid = 0; qid < q; qid++) {
//         int t; cin >> t;
//         // if(n >= 100000 && qid == 0 && t == 1) {
//         //     assert(0);
//         // }
//         // int t = rng() % 2;
//         if(t == 1) {
//             int pp, xp; cin >> pp >> xp;
//             // int pp = rng() % n;
//             // int xp = rng() % n;
//             int p = (pp + last) % n;
//             int x = (xp + last) % n;

//             int block_idx = p / BS;
//             int prev_val = a[p];

//             a[p] = x;

//             //remove 
//             for(int i = block_idx; i < MAXN / BS; i++) {
//                 bcp[i][prev_val]--;
//             }

//             for(int l = 0; l <= block_idx; l++) {
//                 for(int r = block_idx; r < MAXN / BS; r++) {
//                     pc[l][r] -= get_bcp(l, r, prev_val);
//                 }
//             }

//             //add
//             for(int l = 0; l <= block_idx; l++) {
//                 for(int r = block_idx; r < MAXN / BS; r++) {
//                     pc[l][r] += get_bcp(l, r, x);
//                 }
//             }

//             for(int i = block_idx; i < MAXN / BS; i++) {
//                 bcp[i][x]++;
//             }
//         } else {
//             int lp, rp; cin >> lp >> rp;
//             // int lp = rng() % n;
//             // int rp = rng() % n;
//             int l = (lp + last) % n;
//             int r = (rp + last) % n;

//             if(r < l) swap(l, r); //GG

//             ll res = 0;

//             if(r - l <= BS * 2) {
//                 for(int i = l; i <= r; i++) {
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = 0;
//                     }
//                     res += lqc[a[i]]++;
//                 }
//             } else {
//                 int lb = (l + BS - 1) / BS;
//                 int rb = (r - BS + 1) / BS;

//                 assert(lb * BS >= l && (rb + 1) * BS - 1 <= r);

//                 res = pc[lb][rb];
//                 for(int i = BS * lb - 1; i >= l; i--) {
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     res += lqc[a[i]]++;
//                 }

//                 for(int i = rb * BS + BS; i <= r; i++) {
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     res += lqc[a[i]]++;
//                 }

//                 ll testres = 0;

//                 for(int i = l; i <= r; i++) {
//                     if(lq[a[i]] != inf) {
//                         lq[a[i]] = inf;
//                         lqc[a[i]] = 0;
//                     }
//                     testres += lqc[a[i]]++;
//                 }
//                 inf++;

//                 // assert(res == testres);
//             }

//             res = 1LL * (r - l) * (r - l + 1) / 2 - res;

//             cout << res << " ";
//             last = res;
//         }
//     }

//     cout << '\n';

//     // ll res = 0;

//     // for(int i = 0; i < 300000; i++) {
//     //     for(int j = 0; j < 4000; j++) {
//     //         res += j;
//     //     }
//     // }

//     // cout << res << '\n';

//     // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// const int MAXN = 100000;
// const int BS = 2000;

// int a[MAXN]; //the current array
// ll pc[MAXN / BS][MAXN / BS]; //answers computed for each interval [l, r]
// int bcp[MAXN / BS][MAXN]; //block counts prefix sum, prefix sums for how many times each value appears in the blocks
// int lq[MAXN], lqc[MAXN]; //latest query this number has been considered in, the current count that this number has appeared in
// ll tri[MAXN + 1];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     clock_t tStart = clock();

//     int n; cin >> n;
//     // int n = 100000;
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         x--;
//         // int x = rng() % n;
//         a[i] = x;
//         bcp[i / BS][x]++;
//     }

//     //compute bcp
//     for(int i = 0; i < MAXN; i++) {
//         for(int j = 1; j < MAXN / BS; j++) {
//             bcp[j][i] += bcp[j-1][i];
//         }
//     }

//     auto get_bcp = [&](int l, int r, int i) -> int {
//         return bcp[r][i] - (l ? bcp[l-1][i] : 0);
//     };

//     for(int i = 0; i <= MAXN; i++) {
//         tri[i] = 1LL * i * (i - 1) / 2;
//     }

//     for(int l = 0; l < MAXN / BS; l++) {
//         for(int r = l; r < MAXN / BS; r++) {
//             for(int i = 0; i < MAXN; i++) {
//                 pc[l][r] += tri[get_bcp(l, r, i)];
//             }
//         }
//     }

//     //     for(int l = 0; l < MAXN / BS; l++) {
//     //         for(int r = l; r < MAXN / BS; r++) {
//     //             ll res = 0;
//     //             for(int i = l * BS; i < r * BS + BS; i++) {
//     //                 if(lq[a[i]] != inf) {
//     //                     lq[a[i]] = inf;
//     //                     lqc[a[i]] = 0;
//     //                 }
//     //                 res += lqc[a[i]]++;
//     //             }

//     //             inf++;

//     //             if(res != pc[l][r]) {
//     //                 cout << "l : " << l << " r : " << r << '\n';
//     //                 cout << "start : " << l * BS << " stop : " << r * BS + BS << '\n';
//     //                 cout << "res : " << res << '\n';
//     //                 cout << "a : ";
//     //                 for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
//     //                 cout << "pc[l][r] : " << pc[l][r] << '\n';
//     //             }

//     //             assert(res == pc[l][r]);

//     //         }
//     //     }

//     ll last = 0;
//     int q; cin >> q;
//     // int q = 300000;
//     for(int qid = 0, inf = 1e9; qid < q; qid++, inf++) {
//         int t; cin >> t;
//         // int t = rng() % 2;
//         if(t == 1) {
//             int pp, xp; cin >> pp >> xp;
//             // int pp = rng() % n;
//             // int xp = rng() % n;
//             int p = (pp + last) % n;
//             int x = (xp + last) % n;

//             int block_idx = p / BS;
//             int prev_val = a[p];

//             a[p] = x;

//             //remove 
//             for(int i = block_idx; i < MAXN / BS; i++) {
//                 bcp[i][prev_val]--;
//             }

//             for(int l = 0; l <= block_idx; l++) {
//                 for(int r = block_idx; r < MAXN / BS; r++) {
//                     pc[l][r] -= get_bcp(l, r, prev_val);
//                 }
//             }

//             //add
//             for(int l = 0; l <= block_idx; l++) {
//                 for(int r = block_idx; r < MAXN / BS; r++) {
//                     pc[l][r] += get_bcp(l, r, x);
//                 }
//             }

//             for(int i = block_idx; i < MAXN / BS; i++) {
//                 bcp[i][x]++;
//             }
//         } else {
//             int lp, rp; cin >> lp >> rp;
//             // int lp = rng() % n;
//             // int rp = rng() % n;

//             int l = (lp + last) % n;
//             int r = (rp + last) % n;

//             // int l = 0, r = n - 1;


//             if(r < l) swap(l, r); //GG

//             if(r - l < BS * 2) continue;

//             ll res = 0, res0, res1;

//             // if(r - l <= BS * 2) {
//             {
//                 res0 = 0;
//                 for(int i = l; i <= r; i++) {
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = 0;
//                     }
//                     res0 += lqc[a[i]]++;
//                 }
//             }
//             // } else {

//             {
//                 int lb = (l + BS - 1) / BS;
//                 int rb = (r - BS + 1) / BS;

//                 assert(lb * BS >= l && (rb + 1) * BS - 1 <= r);
//                 res1 = pc[lb][rb];

//                 for(int i = BS * lb - 1; i >= l; i--) {
//                     if(lq[a[i]] != inf) {
//                         lq[a[i]] = inf;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     res1 += lqc[a[i]]++;
//                 }

//                 for(int i = rb * BS + BS; i <= r; i++) {
//                     if(lq[a[i]] != inf) {
//                         lq[a[i]] = inf;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     res1 += lqc[a[i]]++;
//                 }
//             }
//             // }

//             if(res0 != res1) {
//                 cout << "res0 : " << res0 << " res1 : " << res1 << '\n';


//                 assert(res0 == res1);
//             }


//             res = 1LL * (r - l) * (r - l + 1) / 2 - res;

//             cout << res << " ";
//             last = res;
//         }
//     }

//     cout << '\n';

//     // ll res = 0;

//     // for(int i = 0; i < 300000; i++) {
//     //     for(int j = 0; j < 4000; j++) {
//     //         res += j;
//     //     }
//     // }

//     // cout << res << '\n';

//     // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// const int MAXN = 32;
// const int BS = 4;

// int a[MAXN]; //the current array
// ll pc[MAXN / BS][MAXN / BS]; //answers computed for each interval [l, r]
// int bcp[MAXN / BS][MAXN]; //block counts prefix sum, prefix sums for how many times each value appears in the blocks
// int lq[MAXN], lqc[MAXN]; //latest query this number has been considered in, the current count that this number has appeared in
// ll tri[MAXN + 1];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     clock_t tStart = clock();

//     // int n; cin >> n;
//     int n = 8;
//     for(int i = 0; i < n; i++) {
//         // int x; cin >> x;
//         // x--;
//         int x = rng() % n;
//         a[i] = x;
//         bcp[i / BS][x]++;
//     }

//     //compute bcp
//     for(int i = 0; i < MAXN; i++) {
//         for(int j = 1; j < MAXN / BS; j++) {
//             bcp[j][i] += bcp[j-1][i];
//         }
//     }

//     auto get_bcp = [&](int l, int r, int i) -> int {
//         return bcp[r][i] - (l ? bcp[l-1][i] : 0);
//     };

//     for(int i = 0; i <= MAXN; i++) {
//         tri[i] = 1LL * i * (i - 1) / 2;
//     }

//     for(int l = 0; l < MAXN / BS; l++) {
//         for(int r = l; r < MAXN / BS; r++) {
//             for(int i = 0; i < MAXN; i++) {
//                 pc[l][r] += tri[get_bcp(l, r, i)];
//             }
//         }
//     }

//     // int inf = 1e9;

//     //     for(int l = 0; l < MAXN / BS; l++) {
//     //         for(int r = l; r < MAXN / BS; r++) {
//     //             ll res = 0;
//     //             for(int i = l * BS; i < r * BS + BS; i++) {
//     //                 if(lq[a[i]] != inf) {
//     //                     lq[a[i]] = inf;
//     //                     lqc[a[i]] = 0;
//     //                 }
//     //                 res += lqc[a[i]]++;
//     //             }

//     //             inf++;

//     //             if(res != pc[l][r]) {
//     //                 cout << "l : " << l << " r : " << r << '\n';
//     //                 cout << "start : " << l * BS << " stop : " << r * BS + BS << '\n';
//     //                 cout << "res : " << res << '\n';
//     //                 cout << "a : ";
//     //                 for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
//     //                 cout << "pc[l][r] : " << pc[l][r] << '\n';
//     //             }

//     //             assert(res == pc[l][r]);

//     //         }
//     //     }

//     ll last = 0;
//     // int q; cin >> q;
//     int q = 10000;
//     for(int qid = 0; qid < q; qid++) {
//         // int t; cin >> t;
//         int t = rng() % 2;
//         if(t == 1) {
//             // int pp, xp; cin >> pp >> xp;
//             int pp = rng() % n;
//             int xp = rng() % n;
//             int p = (pp + last) % n;
//             int x = (xp + last) % n;

//             int block_idx = p / BS;
//             int prev_val = a[p];

//             a[p] = x;

//             //remove 
//             for(int i = block_idx; i < MAXN / BS; i++) {
//                 bcp[i][prev_val]--;
//             }

//             for(int l = 0; l <= block_idx; l++) {
//                 for(int r = block_idx; r < MAXN / BS; r++) {
//                     pc[l][r] -= get_bcp(l, r, prev_val);
//                 }
//             }

//             //add
//             for(int l = 0; l <= block_idx; l++) {
//                 for(int r = block_idx; r < MAXN / BS; r++) {
//                     pc[l][r] += get_bcp(l, r, x);
//                 }
//             }

//             for(int i = block_idx; i < MAXN / BS; i++) {
//                 bcp[i][x]++;
//             }
//         } else {
//             // int lp, rp; cin >> lp >> rp;
//             int lp = rng() % n;
//             int rp = rng() % n;
//             int l = (lp + last) % n;
//             int r = (rp + last) % n;

//             if(r < l) swap(l, r); //GG

//             ll res = 0;

//             // if(r - l <= BS * 2) {
//                 for(int i = l; i <= r; i++) {
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = 0;
//                     }
//                     res += lqc[a[i]]++;
//                 }
//             // } else {
//             ll res0 = res;
//             qid++;

//                 int lb = (l + BS - 1) / BS;
//                 int rb = (r - BS + 1) / BS;

//                 if(r - l >= BS * 2 && !(lb * BS >= l && (rb + 1) * BS - 1 <= r)) {
//                     cout << "l : " << l << " r : " << r << '\n';
//                     cout << "lb : " << lb << " rb : " << rb << '\n';
//                 }

//                 assert(!(r - l >= BS * 2) || (lb * BS >= l && (rb + 1) * BS - 1 <= r));

//                 res = pc[lb][rb];
//                 for(int i = BS * lb - 1; i >= l; i--) {
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     res += lqc[a[i]]++;
//                 }

//                 for(int i = rb * BS + BS; i <= r; i++) {
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     res += lqc[a[i]]++;
//                 }
//             // }


//             // cout << res << " ";


//             if(r - l >= BS * 2 && res0 != res) {
//                 cout << "l : " << l << " r : " << r << '\n';
//                 cout << "res slow : " << res0 << " res fast : " << res << '\n';
//                 cout << "a : ";
//                 for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];


//                 int lb = (l + BS - 1) / BS;
//                 int rb = (r - BS + 1) / BS;

//                 cout << "lb : " << lb << " rb : " << rb << '\n';

//                 assert(lb * BS >= l && (rb + 1) * BS - 1 <= r);

//                 res = pc[lb][rb];
//                 cout << "starting res : " << res << '\n';
//                 qid++;
//                 for(int i = BS * lb - 1; i >= l; i--) {
//                     cout << "gogo i-l : " << i << '\n';

//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     cout << "add " << lqc[a[i]] << '\n';
//                     res += lqc[a[i]]++;
//                 }

//                 for(int i = rb * BS + BS; i <= r; i++) {
//                     cout << "gogo i-r : " << i << '\n';
//                     if(lq[a[i]] != qid) {
//                         lq[a[i]] = qid;
//                         lqc[a[i]] = get_bcp(lb, rb, a[i]);
//                     }
//                     cout << "add : " << lqc[a[i]] << '\n';
//                     res += lqc[a[i]]++;
//                 }

//                 cout << "final res : " << res << '\n';

//                 assert(0);

//             }

//             res = 1LL * (r - l) * (r - l + 1) / 2 - res;
//             last = abs(res);
            
//         }
//     }

//     cout << '\n';

//     // ll res = 0;

//     // for(int i = 0; i < 300000; i++) {
//     //     for(int j = 0; j < 4000; j++) {
//     //         res += j;
//     //     }
//     // }

//     // cout << res << '\n';

//     // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

//     return 0;
// }
