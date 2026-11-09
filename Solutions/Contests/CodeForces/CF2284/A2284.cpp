#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> c(n);
    // for(int &x : c) cin >> x;
    
    ll a = 0, b = 0;
    sort(c.rbegin(), c.rend());
    for(int x : c) {
        if(a <= b) {
            a += 1LL << x;
        } else {
            b += 1LL << x;
        }
    }

    cout << a * b << '\n';

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