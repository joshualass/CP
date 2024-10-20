#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, r; cin >> n >> r;

    int happy = 0, singles = 0;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        happy += a / 2 * 2;
        r -= a / 2;
        singles += (a & 1);
    }

    cout << happy + min(singles,r * 2 - singles) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}