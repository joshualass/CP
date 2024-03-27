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

    int cnt = 1;
    for(int i = (n+1) / 2; i < n; i++) {
        if(a[i] != a[i-1]) break;
        cnt++;
    }
    cout << cnt << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}