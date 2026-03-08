#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n); 
    for(ll &x : a) cin >> x;
    vector<ll> p(n), s(n);
    for(int i = 1; i < n; i++) {
        p[i] = p[i-1] + max(0LL, a[i-1] - a[i]);
    }
    for(int i = n - 2; i >= 0; i--) {
        s[i] = s[i+1] + max(0LL, a[i+1] - a[i]);
    }
    for(int qq = 0; qq < m; qq++) {
        int l, r; cin >> l >> r;
        l--; r--;
        if(l < r) {
            cout << p[r] - p[l] << '\n';
        } else {
            cout << s[r] - s[l] << '\n';
        }
    }

    return 0;
}
