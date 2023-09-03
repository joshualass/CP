#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const ll N = 200001;
ll dsu[N];
ll depths[N];
ll sizes[N];

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
    if(depths[x] == depths[y]) {
        dsu[y] = x;
        depths[x]++;
        sizes[x] += sizes[y];
    } else if(depths[x] < depths[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[x] = y;
        sizes[y] += sizes[x];
    }
}

ll binexp(ll base, ll power) {
    if(power == 0) {
        return 1;
    }
    if(power%2 == 0) {
        return binexp(base * base % MOD, power / 2);
    } else {
        return base * binexp(base, power-1) % MOD;
    }
}

void solve() {
    ll n, S; cin >> n >> S;    

    vector<vector<ll>> edges(n-1,vector<ll>(3));
    for(vector<ll> &x: edges) {
        for(ll i = 0; i < x.size(); i++) {
            cin >> x[i];
        }
    }

    sort(edges.begin(), edges.end(), [](const vector<ll>& lhs, const vector<ll>& rhs) {
        return lhs[2] < rhs[2];
    });

    for(ll i = 0; i <= n; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }

    ll total = 0;
    for(ll i = 0; i < n - 1; i++) {
        ll x = find(edges[i][0]-1);
        ll y = find(edges[i][1]-1);
        ll base = S - edges[i][2] + 1;
        ll exp = sizes[x] * sizes[y] - 1;
        // exp %= MOD;
        ll ans = binexp(base, exp);
        // cout << "base: " << base << " exp: " << exp << "\n";
        if(total == 0) {
            total = ans;
        } else {
            total *= ans;
            total %= MOD;
        }
        merge(x,y);
    }
    cout << total << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    ll casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}