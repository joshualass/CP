#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int,10>> a(n);
    vector<vector<ll>> b(n, vector<ll>(11));
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : b) for(auto &y : x) cin >> y;

    ll res = LLONG_MIN;

    for(int bm = 1; bm < 1 << 10; bm++) {
        // int ok = 1;
        // for(int j = 0, t = bm; j < 5; j++, t /= 4) {
        //     if(t % 4 == 0) ok = 0;
        // }
        // if(!ok) continue;
        ll cur = 0;
        for(int i = 0; i < n; i++) {
            int cnt = 0;
            for(int j = 0; j < 10; j++) {
                if(((bm >> j) & 1) && a[i][j]) cnt++;
            }
            cur += b[i][cnt];
        }
        res = max(res, cur);
    }

    cout << res << '\n';

    return 0;
}
