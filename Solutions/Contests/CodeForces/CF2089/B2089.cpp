#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    // int n = 200000;
    // ll k = 42069;
    // vector<ll> a(n, 42069);
    // vector<ll> b(n, 40000);
    // b[0] = 1e9;
    // cout << accumulate(a.begin(), a.end(), 0LL) << endl;
    // cout << accumulate(b.begin(), b.end(), 0LL) << endl;
    set<int> as, bs;
    for(int i = 0; i < n; i++) {
        as.insert(i);
        bs.insert(i);
    }

    // cout << "build sets done" << endl;

    ll res = 0;
    k = accumulate(a.begin(), a.end(), 0LL) - k;
    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    vector<vector<int>> usa(n);

    //{idx, len}
    auto get_next_lb = [&](int i, set<int>& s) -> array<int,2> {
        if(s.empty()) return {-1,-1};
        auto lb = s.lower_bound(i);
        if(lb != s.end()) {
            return {*lb, *lb - i};
        }
        lb = s.lower_bound(0);
        return array<int,2>{*lb, *lb + (n - i)};
    };

    auto get_next_ub = [&](int i, set<int>& s) -> array<int,2> {
        if(s.empty()) return {-1,-1};
        auto ub = s.upper_bound(i);
        if(ub != s.end()) {
            return {*ub, *ub - i};
        }
        ub = s.lower_bound(0);
        return array<int,2>{*ub, *ub + (n - i)};
    };

    auto add_queue = [&](int i) -> void {
        // cout << "add queue called i : " << i << endl;
        array<int,2> next_a = get_next_ub(i, as);
        array<int,2> next_b = get_next_lb(i, bs);
        if(next_a[1] <= next_b[1]) { //a <= b. add to usa
            usa[next_a[0]].push_back(i);
        } else {
            pq.push({next_b[1], i, next_b[0]});
        }
    };

    for(int i = 0; i < n; i++) {
        add_queue(i);
        // pq.push({0,i,i});
    }

    // cout << "add queue done" << endl;

    int c = 0;

    while(k > 0) {
        assert(pq.size());
        auto [time, ai, bi] = pq.top();
        pq.pop();

        // cout << "make it here" << endl;

        // c++;
        // if(c % 10 == 0) {
        //     cout << "c : " << c << endl;
        // }

        // cout << "time : " << time << " ai : " << ai << " bi : " << bi << endl;

        ll t = min(a[ai], b[bi]);
        a[ai] -= t;
        b[bi] -= t;
        k -= t;
        res = max(res, time + 1);
        
        if(a[ai] == 0) as.erase(ai);
        if(b[bi] == 0) bs.erase(bi);

        if(a[ai]) add_queue(ai);
        else {
            assert(usa[ai].size() <= 1);
            for(int x : usa[ai]) add_queue(x);
            usa[ai].clear();
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// void solve() {
//     ll n, k; cin >> n >> k;
//     vector<ll> a(n), b(n);
//     for(ll &x : a) cin >> x;
//     for(ll &x : b) cin >> x;
//     vector<ll> p(n + 1);
//     for(int i = 1; i <= n; i++) p[i] = p[i-1] + b[i-1];
//     auto get_sum = [&](auto self, ll i, ll rounds) -> ll {
//         ll r = min(n, i + rounds);
//         ll res = p[r] - p[i];
//         rounds -= r-i;
//         if(rounds) {
//             res += self(self, 0, rounds);
//         }
//         return res;
//     };
//     ll l = 0, r = n;
//     while(l != r) {
//         ll m = (l + r) / 2;
//         ll use = 0;
//         // cout << "m : " << m << '\n';
//         for(int i = 0; i < n; i++) {
//             // cout << "i : " << i << " m : " << m << " gs : " << get_sum(get_sum, i, m) << '\n';
//             use += max(0LL, a[i] - get_sum(get_sum, i, m));
//             // cout << "i : " << i << " add use : " << max(0LL, a[i] - get_sum(get_sum, i, m)) << '\n';
//         }
//         // cout << "m : " << m << " use : " << use << '\n';
//         if(use <= k) {
//             r = m;
//         } else {
//             l = m + 1;
//         }
//     }
//     cout << l << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }