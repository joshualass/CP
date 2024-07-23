#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    sort(a.begin(), a.end());

    bool found = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(i == 0 || i != 0 && a[i-1] != a[i]) {
            if((n - i) & 1) found = 1;
        }
    }
    cout << (found ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}