#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> c(n+1), s(n+1,-1e9), b(n+1,-1e9);
    for(int i = 0; i < n; i++) {
        c[i+1] = c[i];
        if(a[i] > c[i+1]) {
            c[i+1]++;
        } else if(a[i] < c[i]) {
            c[i+1]--;
        }
        s[i+1] = max(s[i],c[i]);
        b[i+1] = max(s[i],b[i]);
        if(a[i] > b[i+1]) {
            b[i+1]++;
        } else if(a[i] < b[i+1]) {
            b[i+1]--;
        }
    }
    cout << max(b[n], s[n]) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}