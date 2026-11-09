#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    ll s = 0;
    vector<ll> a, b;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(i % 2 == 0) {
            a.push_back(x);
        } else {
            b.push_back(x);
        }
        s += x;
    }

    ll res = s;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // cout << "s : " << s << endl;
    for(int i = 0; i < min(sz(a), sz(b)); i++) {
        s -= (a[i] + b[i]) * 2;
        // cout << "i : " << i << " s : " << s << endl;
        res = max(res, s);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}