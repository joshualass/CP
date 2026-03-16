#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k, p, m; cin >> n >> k >> p >> m;
    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
    }    
    a[p - 1][1] = 1;

    int res = 0;
    while(1) {
        int best = 0;
        for(int i = 1; i < k; i++) {
            if(a[i][1]) {
                best = i;
            } else if(a[best][1] == 0 && a[i][0] < a[best][0]) {
                best = i;
            }
        }
        if(a[best][0] > m) break;
        m -= a[best][0];
        res += a[best][1];
        a.push_back(a[best]);
        a.erase(a.begin() + best);
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