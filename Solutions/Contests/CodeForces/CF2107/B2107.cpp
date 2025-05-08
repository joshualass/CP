#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    sort(a.begin(), a.end());
    if(a[n-1] - 1 - a[0] > k || a[n - 2] - a[0] > k) {
        cout << "Jerry\n";
        return;
    }
    cout << (accumulate(a.begin(), a.end(), 0LL) & 1 ? "Tom" : "Jerry") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}