#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, k; cin >> n >> k;
    vector<ll> b(n);
    for(ll &x : b) cin >> x;
    sort(b.begin(), b.end());

    auto sub = [&](ll c) -> pair<ll, vector<ll>> {

        ll res = -1;
        vector<ll> a = b;

        for(int i = n - 1; i >= 0; i--) {

            ll nx = (i ? a[i-1] : 0);
            ll sz = n - i;
            ll cur = a[i];

            ll row_sub = min(cur - nx, c / sz);
            c -= row_sub * sz;
            res = cur - row_sub;

            if(row_sub != cur - nx) {
                for(int j = i; j < n; j++) {
                    a[j] = cur - row_sub;
                    if(c) {
                        a[j]--;
                        c--;
                        res = cur - row_sub - 1;
                    }
                }
                break;
            } 
        }

        //return highest q-pos removed
        return {res + 1, a};

    };

    auto add = [&](ll c) -> pair<ll, vector<ll>> {

        ll res = -1;
        vector<ll> a = b;
        for(int i = 0; i < n; i++) {
            ll nx = (i == n - 1 ? 1e12 : a[i+1]);
            ll sz = i + 1;
            ll cur = a[i];

            ll row_add = min(nx - cur, c / sz);
            c -= row_add * sz;
            res = cur + row_add;

            if(row_add != nx - cur) {
                for(int j = i; j >= 0; j--) {
                    a[j] = cur + row_add;
                    if(c) {
                        a[j]++;
                        c--;
                        res = cur + row_add + 1;
                    }
                }
                break;
            }
        }

        return {res, a};
    };

    ll l = 0, r = accumulate(b.begin(), b.end(), 0LL);
    while(l != r) {
        ll m = (l + r + 1) / 2;
        auto [highest_rem, sub_stuff] = sub(m);
        auto [lowest_add, add_stuff] = add(m);
        if(highest_rem - lowest_add >= k + 1) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    // cout << "move cnt : " << l << '\n';
    auto [highest_rem, sub_stuff] = sub(l);

    ll movecnt = 0;

    for(int i = 0; i < n; i++) movecnt += b[i] - sub_stuff[i];
    b = sub_stuff;
    auto [lowest_add, add_stuff] = add(l);
    b = add_stuff;

    ll res = 0;
    for(int i = 0; i < n; i++) res += b[i] * (b[i] + 1) / 2;

    cout << res + movecnt * k << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}