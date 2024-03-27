#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    string s; cin >> s;

    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    vector<ll> p0(n+1);
    vector<ll> p1(n+1);
    vector<ll> s0(n+1);
    vector<ll> s1(n+1);

    for(int i = 0; i < n; i++) {
        p0[i+1] = p0[i];
        p1[i+1] = p1[i];
        s0[i+1] = s0[i];
        s1[i+1] = s1[i];

        if((s[i] == '0') == (i & 1)) {
            p0[i+1] += v[i];
        } else {
            p1[i+1] += v[i];
        }
        if((s[n-i-1] == '0') == (i & 1)) {
            s0[i+1] += v[n-i-1];
        } else {
            s1[i+1] += v[n-i-1];
        }
    }

    ll ans = LLONG_MAX;
    for(int i = 0; i < n - 1; i++) {
        if(n & 1) {
            ans = min(ans, p0[i+1] + s1[n-i-1]);
            ans = min(ans, p1[i+1] + s0[n-i-1]);
        } else {

            ans = min(ans, p0[i+1] + s0[n-i-1]);
            ans = min(ans, p1[i+1] + s1[n-i-1]);
        }
    }

    cout << ans << '\n';

    return 0;
}