#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<array<int,2>> a(n);
    vector<int> p(n * 2 + 1), c(n * 2 + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        if(a[i][0] == a[i][1]) {
            p[a[i][0]] = 1;
            c[a[i][0]]++;
        }
    }
    for(int i = 1; i <= n * 2; i++) {
        p[i] += p[i-1];
    }
    for(int i = 0; i < n; i++) {
        if(a[i][0] == a[i][1]) {
            cout << (c[a[i][0]] == 1);
        } else {
            cout << ((p[a[i][1]] - p[a[i][0] - 1]) != (a[i][1] - a[i][0] + 1));
        }
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}