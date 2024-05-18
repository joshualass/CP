#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//hay miguel

void solve() {
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<ll> p0(31);
    vector<ll> p1(31);
    vector<ll> s0(31);
    vector<ll> s1(31);

    for(int i = n - 1; i >= 0; i--) {
        for(int bit = 0; bit < 31; bit++) {
            if(a[i] & (1 << bit)) {
                swap(s0[bit],s1[bit]);
                s1[bit]++;
            } else {
                s0[bit]++;
            }
        }
    }

    ll res = 0;

    for(int i = 0; i < n; i++) {

        for(int bit = 0; bit < 31; bit++) {
            if(a[i] & (1 << bit)) {
                s1[bit]--;
                swap(s0[bit],s1[bit]);
            } else {
                s0[bit]--;
            }
        }

        int msb = 31 - __builtin_clz(a[i]);

        s0[msb]++;
        p0[msb]++;
        res += p0[msb] * s1[msb] + p1[msb] * s0[msb];
        s0[msb]--;
        p0[msb]--;

        for(int bit = 0; bit < 31; bit++) {

            if(a[i] & (1 << bit)) {
                swap(p0[bit],p1[bit]);
                p1[bit]++;

            } else {
                p0[bit]++;

            }


        }


    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}