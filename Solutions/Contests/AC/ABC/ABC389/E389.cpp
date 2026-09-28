#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//how to ternary search over integers
//try a non-search approach

/*
new approach - binary search the threshold square
our condition is that it is good when all the numbers can make the threshold
no ternary search on non-unimodal data
faster than old binary search

approaches considered
first, try binary searching the answer -> TLE
second, try binary searching the cost per unit -> WA
Considered ternary search
third, try binary searching the min cost for buying another unit for all units. this should work. 
This third approach came about after considering a greedy approach. 
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll solve(ll n, ll m, vector<ll> a) {
    auto f = [&](ll t) -> bool {
        ll bal = m;
        for(int i = 0; i < n; i++) {
            ll k = (t/a[i] + 1) / 2;
            if(1e18 / k < k * a[i]) return 0;
            bal -= k * k * a[i];
            if(bal < 0) return 0;
        }
        return 1;

        // ll bal = m;
        // for(int i = 0; i < n; i++) {
        //     ll buy = t / a[i];
        //     if(1e18 / buy < buy * a[i]) return 0;
        //     bal -= buy * buy * a[i];
        //     if(bal < 0) return 0;
        // }
        // return 1;
    };

    ll lo = 0, hi = 1e18;
    while(lo != hi) {
        ll mid = (lo + hi + 1) / 2;
        if(f(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    // cout << "lo : " << lo << '\n';

    ll res = 0;
    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    vector<ll> b(n);
    for(int i = 0; i < n; i++) {
        ll k = (lo/a[i] + 1) / 2;
        m -= k * k * a[i];
        res += k;
        pq.push({a[i] * (2 * k + 1), i, k});
        b[i] += k;
        // ll buy = lo / a[i];
        // m -= buy * buy * a[i];
        // res += buy;
        // pq.push({a[i] * (2 * buy + 1), i, buy});
        // cout << "i : " << i << " nextcost : " << a[i] * (2 * buy + 1) << '\n';
        // b[i] += buy;
    }

    // cout << "solve partial sol'n : " << b << '\n';

    // cout << "res0 : " << res << '\n';
    // cout << "rem0 : " << m << '\n';

    while(pq.size()) {
        auto [next_cost, i, prev_buy] = pq.top();
        pq.pop();
        if(m >= next_cost) {
            res++;
            m -= next_cost;
            prev_buy++;
            pq.push({a[i] * (2 * prev_buy + 1), i, prev_buy});
            b[i]++;
        }
    }

    // cout << res << '\n';

    // cout << "rem bal : " << m << '\n';
    // cout << "solver sol'n : " << b << '\n';
    return res;
}

ll greedy(ll n, ll m, vector<ll> a) {
    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    for(int i = 0; i < n; i++) {
        pq.push({a[i], i, 0});
    }
    ll res = 0;
    vector<ll> b(n);
    while(pq.size()) {
        auto [c, i, p] = pq.top();
        pq.pop();
        if(m >= c) {
            m -= c;
            res++;
            p++;
            pq.push({a[i] * (2 * p + 1), i, p});
            b[i]++;
        }
    }
    cout << "greedy sol'n : " << b << '\n';
    return res;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const ll inf = 1000;
const ll pmax = 10;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    // ll n = 1, m = 1e18;
    // vector<ll> a(n,1);
    // iota(a.begin(), a.end(), 1LL);

    // for(int i = 0; i < 10000; i++) {
    //     // cout << "i : " << i << endl;
    //     ll n = 10, m = rng() % inf;
    //     vector<ll> a(n);
    //     for(int j = 0; j < 10; j++) {
    //         a[j] = rng() % pmax + 1;
    //     }
    //     if(greedy(n,m,a) != solve(n,m,a)) {
    //         cout << "greedy : " << greedy(n,m,a) << '\n';
    //         cout << "solve : " << solve(n,m,a) << '\n';
    //         cout << "n : " << n << " m : " << m << " a : " << a << '\n';
    //         return 0;
    //     }
    // }

    // cout << "greedy ... \n" << greedy(n,m,a) << '\n';
    // cout << "solve ... \n" << solve(n,m,a) << '\n';

    cout << solve(n,m,a) << '\n';


    return 0;
}

/*
lo : 2236085
447210023988
rem bal : 1012589
*/

//binary search not fast enough

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     // ll n, m; cin >> n >> m;
//     ll n = 2e5, m = 1e18;
//     vector<ll> a(n,1);
//     // for(ll &x : a) cin >> x;
//     ll lo = 0, hi = 2e14;
//     while(lo != hi) {
//         ll mid = (lo + hi + 1) / 2;
//         ll bal = m, quant = 0;
//         priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;

//         cout << "mid : " << mid << endl;

//         for(int i = 0; i < n; i++) {
//             pq.push({a[i], i, 0});
//         }

//         int t = 0;

//         while(pq.size()) {
//             if(t++ % 200000 == 0) {
//                 cout << t << endl;
//             }
//             auto [next_min_cost, i, prev_k] = pq.top();
//             pq.pop();

//             bal += prev_k * prev_k * a[i];

//             ll max_avg_cost = bal / (mid - quant);
//             ll max_buy = max_avg_cost / a[i];

//             bal -= max_buy * max_buy * a[i];
//             quant += max_buy - prev_k;

//             if(max_buy != prev_k && a[i] * (2 * max_buy + 1) <= bal) {
//                 pq.push({a[i] * (2 * max_buy + 1), i, max_buy});
//             }

//             if(quant >= mid) break;
//         }

//         // for(int i = 0; i < n; i++) {
//         //     ll max_avg_cost = bal / (mid - quant);
//         //     ll max_buy = max_avg_cost / a[i];
//         //     quant += max_buy;
//         //     bal -= max_buy * max_buy * a[i];
//         //     pq.push({a[i] * (2 * max_buy + 1), i, max_buy + 1});
//         //     if(quant >= mid) break;
//         // }
//         // while(bal > 0 && quant < mid) {
//         //     auto [cost, idx, prev_max_buy] = pq.top();
//         //     pq.pop();
//         //     if(cost > bal) break;
//         //     bal -= cost;
//         //     quant++;
//         //     pq.push({a[idx] * (2 * prev_max_buy + 1), idx, prev_max_buy + 1});
//         // }

//         cout << "donebs" << endl;

//         if(quant >= mid) {
//             lo = mid;
//         } else {
//             hi = mid - 1;
//         }
//     }

//     cout << lo << '\n';

//     return 0;
// }