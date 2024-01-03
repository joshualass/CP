#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    ll sum = 0;
    int evencnt = 0;
    int oddcnt = 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        sum += num;
        if(num & 1) {
            oddcnt++;
        } else {
            evencnt++;
        }
        if(oddcnt == 1) {
            if(evencnt) {
                cout << sum - 1 << ' ';
            } else {
                cout << sum << ' ';
            }
        } else {
            cout << sum - oddcnt + (oddcnt + 1) / 3 * 2 << ' ';
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