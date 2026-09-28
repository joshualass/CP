#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return abs(lhs) < abs(rhs);
    });

    int ok = 1;

    int _g = gcd(a[0], a[1]);
    int ta = a[0] / _g, tb = a[1] / _g;

    for(int i = 2; i < n; i++) {
        int g = gcd(a[i], a[i-1]);

        int ca = a[i-1] / g, cb = a[i] / g;
        if(ca < 0 && ta > 0 || ca > 0 && ta < 0) {
            ca *= -1;
            cb *= -1;
        }

        if(ca != ta || cb != tb) {
            // cout << "ta : " << ta << " tb : " << tb << " ca : " << ca << " cb : " << cb << '\n';    
            ok = 0;
        }
        
    }

    // int mx = *max_element(a.begin(), a.end());
    // if(abs(count(a.begin(), a.end(), mx) - count(a.begin(), a.end(), - mx)) <= 1 && abs(count(a.begin(), a.end(), mx) + count(a.begin(), a.end(), - mx)) == n) ok = 1;

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}