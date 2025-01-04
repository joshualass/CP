#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int c = 1;
    vector<int> a(n);
    for(int i = k - 1; i < n; i += k) {
        a[i] = c++;
    }
    for(int i = 0; i < n; i++) {
        if(a[i] == 0) {
            a[i] = c++;
        }
        cout << a[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}