#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m, x; cin >> n >> m >> x;
    vector<int> a(n);
    a[x-1] = 1;
    for(int i = 0; i < m; i++) {
        vector<int> u(n);
        int r; cin >> r;
        char c; cin >> c;
        if(c == '0' || c == '?') {
            for(int j = 0; j < n; j++) {
                u[(j + r) % n] |= a[j];
            }
        }
        if(c == '1' || c == '?') {
            for(int j = 0; j < n; j++) {
                u[(j - r + n) % n] |= a[j];
            }
        }
        swap(a,u);
    }
    cout << count(a.begin(), a.end(),1) << '\n';
    for(int i = 0; i < n; i++) {
        if(a[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}