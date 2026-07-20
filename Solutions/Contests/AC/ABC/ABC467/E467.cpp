#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

int testing = 0;
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll solve_fast(ll n, ll m, vector<ll> a, vector<ll> b) {

    vector<ll> start(n);
    for(ll i = 1; i < n; i++) {
        start[i] = (b[i - 1] - start[i - 1] + m) % m;
    }

    ll init_cost = 0;
    map<ll,ll> events;

    for(ll i = 0; i < n; i++) {
        init_cost += (start[i] - a[i] + m) % m;
        if(i % 2 == 0) {
            if(a[i] != start[i]) {
                events[(a[i] - start[i] + m) % m] -= m;
            }
        } else {
            ll t = (start[i] - a[i] + m + 1) % m;
            if(t) {
                events[t] += m;
            }
        }
    }

    events[0] += 0;

    // cout << "ic : " << init_cost << endl;
    // cout << "e : " << events << endl;

    ll res = LLONG_MAX;
    for(auto [x, delta] : events) {
        init_cost += delta;
        ll cost = init_cost;
        if(n % 2 == 1) {
            cost += x;
        }
        res = min(res, cost);
    }

    return res;
}

ll solve_slow(ll n, ll m, vector<ll> a, vector<ll> b) {

    // cout << "testing n : " << n << " m : " << m << endl;
    // cout << "a : " << a << endl;
    // cout << "b : " << b << endl;

    ll res = LLONG_MAX;
    vector<int> start(n);
    for(int i = 1; i < n; i++) {
        start[i] = (b[i - 1] - start[i-1] + m) % m;
    }

    for(int i = 0; i < m; i++) {
        ll ops = 0;
        for(int j = 0; j < n; j++) {
            ops += (start[j] - a[j] + m) % m;
            if(j % 2 == 0) {
                start[j] = (start[j] + 1) % m;
            } else {
                start[j] = (start[j] - 1 + m) % m;
            }
        }
        res = min(res, ops);
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(testing == 0) {
        ll n, m; cin >> n >> m;
        vector<ll> a(n), b(n - 1);
        for(ll &x : a) cin >> x;
        for(ll &x : b) cin >> x;
        cout << solve_fast(n, m, a, b) << '\n';
    } else {

        for(int tc = 0; tc < 1000; tc++) {
            int n = rng() % 5 + 2;
            int m = rng() % 10 + 3;
            vector<ll> a(n), b(n - 1);
            for(ll &x : a) x = rng() % m;
            for(ll &x : b) x = rng() % m;

            ll fast = solve_fast(n, m, a, b);
            ll slow = solve_slow(n, m, a, b);

            // ll slow = fast;
            if(fast != slow) {
                cout << "fast : " << fast << " slow : " << slow << endl;
                cout << n << " " << m << endl;
                cout << a << endl;
                cout << b << endl;
                return 0;
            }
        }
        cout << "ALL OK!" << endl;
    }

    return 0;
}
