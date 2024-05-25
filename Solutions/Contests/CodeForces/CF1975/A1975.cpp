#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = 0; i < n; i++) {
        bool ok = 1;
        for(int j = 1; j < n; j++) {
            int p = (i + j - 1) % n;
            int b = (i + j) % n;
            if(a[b] < a[p]) ok = 0;
        }
        if(ok) {
            cout << "Yes\n";
            return;
        }
    }

    cout << "No\n";
    return;
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}