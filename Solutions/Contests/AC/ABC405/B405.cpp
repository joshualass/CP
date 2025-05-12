#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int res = n;
    for(int i = 0; i < n; i++) {
        set<int> s;
        for(int j = 0; j <= i; j++) {
            if(a[j] <= m) s.insert(a[j]);
        }
        if(s.size() < m) res = n - i - 1;
    }

    cout << res << '\n';

    return 0;
}
