#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll calc_score(ll coord, ll a, ll b, vector<ll> &prefix, vector<ll> &coords) {
    ll idx = coords[coord];
    ll n = prefix.size() - 1;
    ll after_cnt = n - idx;
    ll after_sum = prefix.back() - prefix[idx];
    ll before_cnt = idx;
    ll before_sum = prefix[idx];

    return (after_sum - after_cnt * coord) * b + (before_cnt * coord - before_sum) * a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<ll> v(n);

    for(auto &x : v) cin >> x;

    sort(v.begin(), v.end());

    vector<ll> prefix(n + 1);
    for(int i = 1; i <= n; i++) {
        prefix[i] = prefix[i-1] + v[i-1];
    }

    vector<ll> coords(1e6 + 1);
    int l = 0;

    for(int i = 0; i < 1e6 + 1; i++) {
        while(l != n && v[l] < i) {
            l++;
        }
        coords[i] = l;
    }

    int q; cin >> q;

    for(int i = 0; i < q; i++) {
        ll a, b; cin >> a >> b;

        ll lo = 0, hi = 1e6;

        while(hi - lo > 5) {
            ll m1 = lo + (hi - lo) / 3;
            ll m2 = lo + ((hi - lo) * 2 + 1) / 3;
            
            ll m1score = calc_score(m1, a, b, prefix, coords);
            ll m2score = calc_score(m2,a,b,prefix,coords);

            if(m1score < m2score) {
                hi = m2;
            } else {
                lo = m1;
            }

        }
        ll ans = LLONG_MAX;
        for(ll i = lo; i <= hi; i++) {
            ans = min(ans, calc_score(i,a,b,prefix,coords));
        }
        cout << ans << '\n';
    }

    return 0;
}