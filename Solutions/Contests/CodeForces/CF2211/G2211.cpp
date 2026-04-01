#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll s = accumulate(a.begin(), a.end(), 0LL);
    ll p = 0;

    ll sum = s;

    int f = 0;

    vector<int> b(n + 1);
    b[0] = 1;
    for(int i = 0; i < n; i++) {
        if(a[i] * n == sum && b[i]) b[i+1] = 1;
        if(i > 0 && (a[i-1] + a[i]) * n == sum * 2 && b[i-1]) b[i+1] = 1;
        p += a[i];
        s -= a[i];
        if(i + 1 < n) {
            if(p * (n - i - 1) < s * (i + 1)) {
                // cout << "f good i : " << i << " p : " << p << " s : " << s << endl;    
                f = 1;
            }
        }
    }

    if(b[n]) f = 1;
    cout << (f ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}