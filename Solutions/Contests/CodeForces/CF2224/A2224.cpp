#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(auto &x : a) cin >> x;

    for(int i = n - 2; i >= 0; i--) {
        a[i] = max(a[i], a[i] + a[i+1]);
    }
    
    int res = 0;
    
    for(auto x : a) {
        if(x > 0) res++;
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