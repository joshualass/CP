#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    n++;
    int ans = 0;
    int mult = 1;
    // cout << "n : " << n << '\n';
    for(int dig = 0; dig < 6; dig++) {
        int cycles = n / (mult * 10);
        ans += cycles * mult * 45;
        int leftover = n - cycles * mult * 10;
        int partial = leftover / mult;
        ans += partial * (partial - 1) / 2 * mult;
        int partial_leftover = leftover - partial * mult;
        ans += partial * partial_leftover;
        // cout << "mult : " << mult << " cycles : " << cycles << " lo : " << leftover << " p : " << partial << " pl : " << partial_leftover << '\n';
        // cout << "cycle add : " << cycles * mult * 45 << " partial add : " << partial * (partial - 1) / 2 * mult << " partial leftover add : " << partial * partial_leftover << '\n';
        mult *= 10;
    }

    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}