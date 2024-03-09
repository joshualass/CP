#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n * 2);
    for(int &x : v) cin >> x;
    sort(v.begin(), v.end());
    int sum = 0;
    for(int i = 0; i < n * 2; i += 2) {
        sum += v[i];
    }
    cout << sum << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}