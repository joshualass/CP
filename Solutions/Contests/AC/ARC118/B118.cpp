#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll k, n, m; cin >> k >> n >> m;
    ll in = 0;
    vector<ll> a(k), b(k);
    for(ll &x : a) cin >> x;

    auto get_score = [&](ll idx, ll cnt) -> pair<ld,int> {
        ll num = cnt * n - a[idx] * m;
        return {abs(((ld) num) / n * m), idx};
    };

    priority_queue<pair<ld,int>, vector<pair<ld,int>>, greater<pair<ld,int>>> pqI, pqD;
    for(int i = 0; i < k; i++) {
        ll est = a[i] * m / n;
        ll best = est;
        pair<ld,int> curr_best = get_score(i, est);
        for(int j = -2; j <= 2; j++) {
            if(est + j >= 0 && est + j <= m && get_score(i, est + j) < curr_best) {
                best = est + j;
                curr_best = get_score(i, est + j);
            }
        }
        in += best;
        b[i] = best;
        if(best + 1 <= m) {
            pqI.push(get_score(i, best + 1));
        }
        if(best - 1 >= 0) {
            pqD.push(get_score(i, best - 1));
        }
    }

    while(in > m) {
        auto [_, idx] = pqD.top();
        pqD.pop();
        b[idx]--;
        if(b[idx] - 1 >= 0) {
            pqD.push(get_score(idx, b[idx] - 1));
        }
        in--;
    }

    while(in < m) {
        auto [_, idx] = pqI.top();
        pqI.pop();
        b[idx]++;
        if(b[idx] + 1 <= m) {
            pqI.push(get_score(idx, b[idx] + 1));
        }
        in++;
    }

    for(int i = 0; i < k; i++) {
        cout << b[i] << " \n"[i == k - 1];
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef __int128_t lll;
// typedef long double ld;
// using namespace std;

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << (ll) arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// struct CompMin {
//     bool operator()(array<lll,4> a, array<lll,4> b) {
//         return a[0] * b[1] > b[0] * a[1];
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll _k, _n, _m; cin >> _k >> _n >> _m;
//     lll k = _k, n = _n, m = _m;

//     CompMin comp;

//     vector<lll> a(k);
//     for(auto &x : a) {
//         ll y; cin >> y;
//         x = y;
//     }

//     auto get_frac = [&](int idx, lll cnt) -> array<lll,4> {
//         lll bi = cnt, ai = a[idx];
//         lll num = bi * n - ai * m;
//         if(num < 0) {
//             num *= -1;
//         }
//         return {num, n * m, idx, cnt};
//     };

//     priority_queue<array<lll,4>, vector<array<lll,4>>, CompMin> pqInc, pqDec;
//     vector<lll> b(k);
//     lll cnt_in = 0;

//     for(int i = 0; i < k; i++) {
//         lll est = a[i] * m / n;
//         array<lll,4> cur = get_frac(i,est);
//         for(int j = -100; j <= 100; j++) {
//             if(est + j >= 0 && est + j <= n && comp(cur,get_frac(i,est+j))) {
//                 cur = get_frac(i,est+j);
//             }
//         }
//         // cout << "i : " << i << " cur : " << cur << '\n';
//         if(cur[3] + 1 <= m) {
//             pqInc.push(get_frac(i, cur[3] + 1));
//         }
//         if(cur[3] - 1 >= 0) {
//             pqDec.push(get_frac(i, cur[3] - 1));
//         }
//         cnt_in += cur[3];
//         b[i] = cur[3];
//     }

//     // cout << "in : " << (ll) cnt_in << " target : " << (ll) m << '\n';
    
//     while(cnt_in > m) {
//         assert(pqDec.size());
//         array<lll,4> t = pqDec.top();
//         pqDec.pop();
//         // cout << "tdec : " << t << '\n';
//         b[t[2]]--;
//         if(b[t[2]] - 1 >= 0) {
//             pqDec.push(get_frac(t[2], b[t[2]] - 1));
//         }
//         cnt_in--;
//     }

//     while(cnt_in < m) {
//         assert(pqInc.size());
//         array<lll,4> t = pqInc.top();
//         pqInc.pop();
//         // cout << "tinc : " << t << '\n';
//         b[t[2]]++;
//         if(b[t[2]] + 1 <= m) {
//             pqInc.push(get_frac(t[2], b[t[2]] + 1));
//         }
//         cnt_in++;
//     }

//     for(int i = 0; i < k; i++) {
//         cout << (ll) b[i] << " \n"[i == k - 1];
//     }

//     return 0;
// }