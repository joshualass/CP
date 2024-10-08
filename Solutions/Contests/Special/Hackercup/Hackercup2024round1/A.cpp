
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    

    int n; cin >> n;
    vector<array<ld,2>> a(n);
    for(auto &x : a) cin >> x[0] >> x[1];

    ld l = LLONG_MIN;
    ld r = LLONG_MAX;

    for(int i = 0; i < n; i++) {
        ld dist = i + 1;

        if(a[i][0] != 0) {
            r = min(r, dist / a[i][0]);
        }
        l = max(l, dist / a[i][1]);
    }

    if(r + 0.00000001 > l) {
        cout << l << '\n';
    } else {
        cout << -1 << '\n';
    }


}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}