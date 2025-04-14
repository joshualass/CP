#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int x, n, m; cin >> x >> n >> m;
    n = min(n, 50);
    m = min(m, 50);
    int t = x;
    for(int i = 0; i < m; i++) t = (t + 1) / 2;
    for(int i = 0; i < n; i++) t = t / 2;
    cout << t << " ";
    t = x;
    for(int i = 0; i < n; i++) t = t / 2;
    for(int i = 0; i < m; i++) t = (t + 1) / 2;
    cout << t << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}