#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    vector<int> a(3);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    cout << min(a[1] - a[0], a[2] - a[1]) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}