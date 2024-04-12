#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll dist[10000];
const ll maxd = 13; 
ll powpow[maxd+1];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    ll res = 0;
    for(ll i = 0; i < k; i++) {
        ll x, y, p; cin >> x >> y >> p;
        x--; y--;
        vector<ll> v;
        for(ll j = max(0LL, x - maxd); j <= min(n - 1, x + maxd); j++) {
            for(ll k = max(0LL, y - maxd); k <= min(m - 1, y + maxd); k++) {
                if(a[j][k] == '#') {
                    v.push_back(dist[(x-j) * (x-j) + (y-k) * (y-k)]);
                    cout << "huh : " << (x-j) * (x-j) + (y-k) * (y-k) << " " << dist[(x-j) * (x-j) + (y-k) * (y-k)] << '\n';
                }
            }
        }
        sort(v.begin(), v.end());
        ll lo = 0;
        ll best = 0;
        for(ll i = 1; i <= maxd; i++) {
            while(lo != v.size() && v[lo] <= i) lo++;
            best = max(best, lo * p - powpow[i]);
        }
        cout << "i : " << i << " best : " << best << '\n';
        cout << "v ? " << v << '\n';
        res += best;
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    powpow[0] = 0;
    powpow[1] = 3;
    for(ll i = 2; i <= maxd; i++) {
        powpow[i] = powpow[i-1] * 3;
    }
    for(ll i = 0; i < 10000; i++) {
        ll j = 0;
        while(j * j < i) j++;
        dist[i] = j;
    }
    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}