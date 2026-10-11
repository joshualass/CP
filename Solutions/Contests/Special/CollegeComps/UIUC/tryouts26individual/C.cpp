#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int N = 1e6;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k; cin >> k;
    vector<int> a(N), b(N);
    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        a[x] = 1;
    }
    cin >> k;
    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        b[x] = 1;
    }

    array<int,4> dp = {};
    for(int i = 0; i < N; i++) {
        if(a[i] || b[i]) {
            array<int,4> ndp = dp;
            int nx = a[i] + (b[i] << 1);
            for(int bm = 0; bm < 4; bm++) {
                int ok = 1;
                if((bm & 1) == 0 && a[i] == 0) continue;
                if((bm & 2) == 0 && b[i] == 0) continue;
                ndp[nx] = max(ndp[nx], 1 + dp[bm]);
            }
            dp = ndp;
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}
