#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef vector<int> vi;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    stack<array<int,2>> s; // {height, low_after}
    int res = 0;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        int lo = INT_MAX;
        while(s.size() && s.top()[0] < x) {
            lo = min(lo, s.top()[1]);
            res = max(res, s.top()[0] - lo);
            s.pop();
        }   
        if(s.size()) s.top()[1] = lo;
        if(s.size()) res = max(res, x - s.top()[1]);
         
        s.push({x,x});
    }

    cout << res << '\n';

    // vi a(n);
    // for(int& x : a) cin >> x;
    // vi pfx(n + 1, 0), sfx(n + 1, 0);
    // for(int i = 1; i <= n; i++) pfx[i] = max(pfx[i - 1], a[i - 1]);
    // for(int i = n - 1; i >= 0; i--) sfx[i] = max(sfx[i + 1], a[i]);
    // int ans = 0;
    // for(int i = 0; i < n; i++) {
    //     int cval = min(pfx[i], sfx[i]);
    //     ans = max(ans, cval - a[i]);
    // }
    // cout << ans << "\n";

    return 0;
}
