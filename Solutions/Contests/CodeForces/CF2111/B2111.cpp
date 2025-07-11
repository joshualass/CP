#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<int> f = {0, 1, 2};

void solve() {
    
    int n, m; cin >> n >> m;

    for(int i = 0; i < m; i++) {
        vector<int> a(3);
        for(int &x : a) cin >> x;
        sort(a.begin(), a.end());
        cout << (a[2] >= f[n] + f[n-1] && a[0] >= f[n]);
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(f.size() <= 10) f.push_back(f[f.size() - 2] + f[f.size() - 1]);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}