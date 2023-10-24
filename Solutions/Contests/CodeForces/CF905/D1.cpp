#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n,1);
    vector<int> b(n);
    for(int i = 1; i < n; i++) {
        cin >> a[i];
    }
    for(auto &x : b) cin >> x;

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int ops = 0;
    int bptr = 0;
    for(int i = 0; i < n; i++) {
        // cout << "i: " << i << " bptr: " << bptr << "\n";
        while(n - ops > i && a[i] >= b[bptr]) {
            // cout << "a val: " << a[i] << " b val: " << b[bptr] << '\n';
            ops++;
            bptr++;
        } 
        bptr++;
    }
    cout << ops << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}