#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;

    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = 1; i < n; i++) {
        if(abs(a[i] - a[i-1]) <= 1) {
            cout << "0\n";
            return;
        }
    }

    int is_inc = 1, is_dec = 1;
    for(int i = 1; i < n; i++) {
        if(!(a[i-1] + 1 < a[i])) is_inc = 0;
        if(!(a[i-1] - 1 > a[i])) is_dec = 0;
    }

    cout << (is_inc || is_dec ? -1 : 1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}