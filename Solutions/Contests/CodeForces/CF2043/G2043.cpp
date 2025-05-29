#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//even if this does not WA, it will likely later TLE as q * n^(2/3) is not intended. 

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 100000;
const int BS = 2000;

int a[MAXN]; //the current array
ll pc[MAXN / BS][MAXN / BS]; //answers computed for each interval [l, r]
int bcp[MAXN / BS][MAXN]; //block counts prefix sum, prefix sums for how many times each value appears in the blocks
int lq[MAXN], lqc[MAXN]; //latest query this number has been considered in, the current count that this number has appeared in
ll tri[MAXN + 1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    clock_t tStart = clock();

    int n; cin >> n;
    // int n = 100000;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        // int x = rng() % n;
        a[i] = x;
        bcp[i / BS][x]++;
    }

    //compute bcp
    for(int i = 0; i < MAXN; i++) {
        for(int j = 1; j < MAXN / BS; j++) {
            bcp[j][i] += bcp[j-1][i];
        }
    }

    auto get_bcp = [&](int l, int r, int i) -> int {
        return bcp[r][i] - (l ? bcp[l-1][i] : 0);
    };

    for(int i = 0; i <= MAXN; i++) {
        tri[i] = 1LL * i * (i - 1) / 2;
    }

    for(int l = 0; l < MAXN / BS; l++) {
        for(int r = l; r < MAXN / BS; r++) {
            for(int i = 0; i < MAXN; i++) {
                pc[l][r] += tri[get_bcp(l, r, i)];
            }
        }
    }

    // int inf = 1e9;

    //     for(int l = 0; l < MAXN / BS; l++) {
    //         for(int r = l; r < MAXN / BS; r++) {
    //             ll res = 0;
    //             for(int i = l * BS; i < r * BS + BS; i++) {
    //                 if(lq[a[i]] != inf) {
    //                     lq[a[i]] = inf;
    //                     lqc[a[i]] = 0;
    //                 }
    //                 res += lqc[a[i]]++;
    //             }

    //             inf++;

    //             if(res != pc[l][r]) {
    //                 cout << "l : " << l << " r : " << r << '\n';
    //                 cout << "start : " << l * BS << " stop : " << r * BS + BS << '\n';
    //                 cout << "res : " << res << '\n';
    //                 cout << "a : ";
    //                 for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    //                 cout << "pc[l][r] : " << pc[l][r] << '\n';
    //             }

    //             assert(res == pc[l][r]);

    //         }
    //     }

    int inf = 1e9;
    ll last = 0;
    int q; cin >> q;
    // int q = 300000;
    for(int qid = 0; qid < q; qid++) {
        int t; cin >> t;
        // if(n >= 100000 && qid == 0 && t == 1) {
        //     assert(0);
        // }
        // int t = rng() % 2;
        if(t == 1) {
            int pp, xp; cin >> pp >> xp;
            // int pp = rng() % n;
            // int xp = rng() % n;
            int p = (pp + last) % n;
            int x = (xp + last) % n;

            int block_idx = p / BS;
            int prev_val = a[p];

            a[p] = x;

            //remove 
            for(int i = block_idx; i < MAXN / BS; i++) {
                bcp[i][prev_val]--;
            }

            for(int l = 0; l <= block_idx; l++) {
                for(int r = block_idx; r < MAXN / BS; r++) {
                    pc[l][r] -= get_bcp(l, r, prev_val);
                }
            }

            //add
            for(int l = 0; l <= block_idx; l++) {
                for(int r = block_idx; r < MAXN / BS; r++) {
                    pc[l][r] += get_bcp(l, r, x);
                }
            }

            for(int i = block_idx; i < MAXN / BS; i++) {
                bcp[i][x]++;
            }
        } else {
            int lp, rp; cin >> lp >> rp;
            // int lp = rng() % n;
            // int rp = rng() % n;
            int l = (lp + last) % n;
            int r = (rp + last) % n;

            if(r < l) swap(l, r); //GG

            ll res = 0;

            if(r - l <= BS * 2) {
                for(int i = l; i <= r; i++) {
                    if(lq[a[i]] != qid) {
                        lq[a[i]] = qid;
                        lqc[a[i]] = 0;
                    }
                    res += lqc[a[i]]++;
                }
            } else {
                int lb = (l + BS - 1) / BS;
                int rb = (r - BS + 1) / BS;

                assert(lb * BS >= l && (rb + 1) * BS - 1 <= r);

                res = pc[lb][rb];
                for(int i = BS * lb - 1; i >= l; i--) {
                    if(lq[a[i]] != qid) {
                        lq[a[i]] = qid;
                        lqc[a[i]] = get_bcp(lb, rb, a[i]);
                    }
                    res += lqc[a[i]]++;
                }

                for(int i = rb * BS + BS; i <= r; i++) {
                    if(lq[a[i]] != qid) {
                        lq[a[i]] = qid;
                        lqc[a[i]] = get_bcp(lb, rb, a[i]);
                    }
                    res += lqc[a[i]]++;
                }

                ll testres = 0;

                for(int i = l; i <= r; i++) {
                    if(lq[a[i]] != inf) {
                        lq[a[i]] = inf;
                        lqc[a[i]] = 0;
                    }
                    testres += lqc[a[i]]++;
                }
                inf++;

                // assert(res == testres);
            }

            res = 1LL * (r - l) * (r - l + 1) / 2 - res;

            cout << res << " ";
            last = res;
        }
    }

    cout << '\n';

    // ll res = 0;

    // for(int i = 0; i < 300000; i++) {
    //     for(int j = 0; j < 4000; j++) {
    //         res += j;
    //     }
    // }

    // cout << res << '\n';

    // printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}

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
