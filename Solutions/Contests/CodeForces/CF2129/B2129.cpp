#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int inv = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] > a[j]) inv++;
        }
    }

    for(int i = 0; i < n; i++) {
        int ah = 0, bh = 0;
        for(int j = i + 1; j < n; j++) if(a[j] > a[i]) ah++;
        for(int j = i - 1; j >= 0; j--) if(a[j] > a[i]) bh++;
        inv -= max(0, bh - ah);
    }

    cout << inv << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}