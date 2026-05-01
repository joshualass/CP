#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

/*
editorialed. not solving this in a very long time. 
*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

ll test = 0;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll k;
    if(test == 0) {
        cin >> k;
    } else {
        k = 17;
    }

    ll n = 1LL << (k + 1);
    vector<ll> a(n);
    if(test == 0) {
        for(ll &x : a) cin >> x;
    } else {
        for(ll &x : a) x = rng() % (1LL << (k * 2));
    }

    vector<array<ll,2>> p(n + 1);
    for(ll i = 0; i < n; i++) {
        p[i+1] = {a[i] ^ p[i][0], i + 1};
    }

    vector<ll> res;

    map<ll,vector<array<ll,2>>> m;
    for(int i = 0; i <= n; i++) {
        m[p[i][0]].push_back(p[i]);
    }

    for(auto [k, v] : m) {
        // cout << "k : " << k << " v : " << v << endl;
        if(v.front()[1] + 2 <= v.back()[1]) {
            res = {v.front()[1], v.front()[1] + 1, v.front()[1] + 1, v.back()[1]};
        }
    }

    sort(p.begin(), p.end());

    ll cnt = 0;

    while(res.empty()) {
        ll i = rng() % (n + 1), j = rng() % (n + 1), k = rng() % (n + 1);
        while(j == i) {
            j = rng() % (n + 1);
        }
        while(k == i || k == j) {
            k = rng() % (n + 1);
        }

        ll t = p[i][0] ^ p[j][0] ^ p[k][0];
        auto it = lower_bound(p.begin(), p.end(), array<ll,2>{t, 0LL});
        while(it != p.end() && (*it)[1] == i || (*it)[1] == j || (*it)[1] == k) it++;
        if(it != p.end() && (*it)[0] == t) {
            res = {p[i][1], p[j][1], p[k][1], (*it)[1]};
            break;
        }
        cnt++;
        // if(cnt > 1000000) {
        //     // cout << "time to stop ... a : " << a << endl;
        //     break;
        // }
    }

    // cerr << "cnt : " << cnt << endl;

    sort(res.begin(), res.end());
    cout << res[0] + 1 << " " << res[1] << " " << res[2] + 1 << " " << res[3] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(test == 0) {
        ll casi; cin >> casi;
        while(casi-->0) solve();
    } else {
        for(ll i = 0; i < 100; i++) {
            solve();
        }
    }


    return 0;
}