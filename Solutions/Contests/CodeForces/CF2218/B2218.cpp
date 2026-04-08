#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n = 7;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x *= -1;
    }
    int sum = accumulate(a.begin(), a.end(), 0);
    int res = INT_MIN;
    for(int i = 0; i < n; i++) {
        res = max(res, sum - a[i] * 2);
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}