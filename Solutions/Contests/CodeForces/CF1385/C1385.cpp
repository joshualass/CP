#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int c = n - 1;
    while(c != 0 && a[c-1] >= a[c]) {
        c--;
    }
    while(c != 0 && a[c-1] <= a[c]) {
        c--;
    }
    cout << c << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}