#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
pf. 

even case, can't waste an op on the last boundary. otherwise, possible

odd case, always round up. 

*/

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int c = 0;
    int l = 0, r = n - 1;
    for(int i = 1; i < n; i++) {
        if(a[i-1] > a[i]) c++;
    }
    while(l + 1 < n && a[l+1] > a[l]) l++;
    while(r - 1 >= 0 && a[r-1] < a[r]) r--;

    if(c & 1) {
        cout << (c + 1) / 2 << '\n';
    } else {
        if(r == 0 || a[r] - a[l] >= r - l) {
            cout << c / 2 << '\n';
        } else {
            cout << 1 + c / 2 << '\n';
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}