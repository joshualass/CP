#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll MAXN = 3e5;

ll SN = sqrt(MAXN);
ll p[MAXN + 1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<vector<array<ll,2>>> queries(n + 1);
    ll q; cin >> q;
    for(ll i = 0; i < q; i++) {
        ll a, b; cin >> a >> b;
        queries[b].push_back({a,i});
    }

    vector<ll> res(q);
    for(ll i = 1; i <= n; i++) {
        if(i <= SN) {
            for(ll j = n - 1; j >= 0; j--) {
                p[j] = a[j];
                if(j + i < n) p[j] += p[j+i];
            }
            for(auto [a, q_id] : queries[i]) {
                res[q_id] = p[a-1];
            }
        } else {
            for(auto [sa, q_id] : queries[i]) {
                ll c = 0;
                for(int j = sa - 1; j < n; j += i) c += a[j];
                res[q_id] = c;
            }
        }
    }

    for(ll r : res) cout << r << '\n';

    return 0;
}