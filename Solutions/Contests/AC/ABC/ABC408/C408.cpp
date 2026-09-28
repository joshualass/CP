#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> p(n + 1);
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--;
        p[l]++;
        p[r]--;
    }

    int res = INT_MAX;
    int c = 0;
    for(int i = 0; i < n; i++) {
        c += p[i];
        res = min(res, c);
    }
    
    cout << res << '\n';

    return 0;
}
