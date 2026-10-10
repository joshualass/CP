#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const ll N = 2e5;
ll dsu[N];
ll sizes[N];

void dsubuild(ll n = N) {
    for(ll i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

ll find(ll x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(ll x, ll y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    dsu[y] = x;
    sizes[x] += sizes[y];
}

void solve() {
    
    ll n, m, q; cin >> n >> m >> q;
    ll s = 0;

    vector<array<ll,3>> e;
    for(ll i = 0; i < m; i++) {
        ll u, v, d; cin >> u >> v >> d;
        u--; v--;
        e.push_back({d, u, v});
        s += d;
    }

    dsubuild(n);
    sort(e.begin(), e.end());

    vector<ll> p(1, 0), c(1, 0);
    ll pt = 0;

    for(auto [d, u, v] : e) {
        if(find(u) != find(v)) {
            p.push_back(p.back() + d);
            merge(u, v);
            c.push_back(d);
        }
    }

    // cout << " p : " << p << endl;

    auto eval = [&](ll i, ll x) -> ll {
        return p[i] + 1LL * (n - i - 1) * (n - i)/ 2 * x ;
    };

    auto comp = [&](ll n1, ll d1, ll n2, ll d2) -> ll {
        return n1 * d2 < n2 * d1;
    };

    for(ll qq = 0; qq < q; qq++) {
        ll x; cin >> x;
        ll l = 0, r = sz(p) - 1;
        while(l != r) {
            ll m = (l + r) / 2;
            if(c[m] < (n - 1 - m) * x) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        // cout << "l : " << l << endl;
        ll best = LLONG_MAX;
        // for(int i = 0; i < sz(p); i++) {
        //     best = min(best, eval(i, x));
        // }
        for(ll i = -10; i <= 10; i++) {
            if(l + i >= 0 && l + i < sz(p)) {
                best = min(best, eval(l + i, x));
            }
        }
        // cout << "best : " << best << endl;
        cout << s - best << " ";
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    for(ll i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}