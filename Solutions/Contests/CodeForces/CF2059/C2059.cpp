#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> a(n,vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> b;
    for(int i = 0; i < n; i++) {
        int c = 0;
        for(int j = n - 1; j >= 0; j--) {
            if(a[i][j] != 1) break;
            c++;
        }
        b.push_back(c);
    }
    sort(b.begin(), b.end());
    int res = 0;
    for(int i = 0; i < n; i++) {
        if(b[i] >= res) res++;
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