#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for(int &x : a) cin >> x;

    sort(a.begin(), a.end());

    for(int i = 0; i < n; i++) {
        int b = a[i / 2], c = a[m - 1 - i / 2];
        if(i & 1) swap(b, c);
        for(int j = 0; j < 3; j++) cout << b << " " << c << " \n"[j == 2];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}