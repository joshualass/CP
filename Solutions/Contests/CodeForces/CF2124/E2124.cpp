#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<ll> p(n), s(n);
    for(int i = 0; i < n; i++) {
        p[i] = a[i];
        if(i) p[i] += p[i-1];
    }
    for(int i = n - 1; i >= 0; i--) {
        s[i] = a[i];
        if(i != n - 1) s[i] += s[i+1];
    }

    if(accumulate(a.begin(), a.end(), 0LL) & 1) {
        cout << "-1\n";
        return;
    }

    for(int piv = 0; piv < n; piv++) {
        ll ps = (piv ? p[piv-1] : 0), ss = (piv == n - 1 ? 0 : s[piv+1]);
        if(ps + a[piv] > ss && ss + a[piv] > ps) {
            // cout << "piv : " << piv << " ps : " << ps << " ss : " << ss << '\n';
            if(a[piv] > ss + ps) {
                cout << "-1\n";
                return;
            }

            ll x = ps + a[piv] - ss;
            
            // cout << "x : " << x << '\n';
            
            vector<ll> b(n);
            
            x /= 2;
            b[piv] = x;

            for(int i = 0; i < piv; i++) {
                // cout << "i : " << i << " x : " << x << '\n';
                b[i] += min(a[i], x);
                x -= b[i];
            }

            cout << "2\n";
            for(int i = 0; i < n; i++) {
                cout << b[i] << " \n"[i == n - 1];
            }
            for(int i = 0; i < n; i++) {
                cout << a[i] - b[i] << " \n"[i == n - 1];
            }
            return;
        }
    }

    cout << "1\n";
    for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}