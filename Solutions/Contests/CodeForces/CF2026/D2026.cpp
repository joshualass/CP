#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<ll> ftriangles(n);
    ll ftsum = 0;
    for(int i = n - 1; i >= 0; i--) {
        ftsum += a[i] * (n-i);
        ftriangles[i] = ftsum;
    }

    vector<ll> ftpsum(n+1);
    vector<ll> rftriangles(n + 1);
    vector<ll> p(n+1);
    for(int i = 1; i <= n; i++) {
        ftpsum[i] = ftpsum[i-1] + ftriangles[i-1];
        p[i] = p[i-1] + a[i-1];
        rftriangles[i] = rftriangles[i-1] + p[i];
    }

    //counts the number of completed triangles 
    auto getcountandrem = [&](ll idx) -> array<ll,2> {
        int l = 0, r = n;
        while(l != r) {
            ll m = (l + r + 1) / 2;
            if(idx >= (n + (n - (m - 1))) * m / 2) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        //now have l completed triangles 
        ll rem = idx - (n + n - (l - 1)) * l / 2;
        return {l, rem};
    };

    auto sumlinesbefore = [&](ll idx) -> ll {
        auto [cnt, rem] = getcountandrem(idx);
        // cout << "idx : " << idx << " cnt : " << cnt << " rem : " << rem << '\n';
        ll res = 0;
        ll fsum = ftpsum[cnt];
        ll remsum = rftriangles[cnt + rem] - rftriangles[cnt] - rem * p[cnt];
        // cout << "idx : " << idx << " fsum : " << fsum << " remsum : " << remsum << '\n'; 
        return fsum + remsum;
    };

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll l, r; cin >> l >> r;
        cout << sumlinesbefore(r) - sumlinesbefore(l-1) << '\n';
    }

    return 0;
}