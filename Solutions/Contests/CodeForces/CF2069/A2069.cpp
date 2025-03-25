#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    n -= 2;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = 2; i < n; i++){
        if(a[i-2] && a[i] && a[i-1] == 0) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}