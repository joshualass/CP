#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int ask(int l, int x) {
    cout << "? " << l << " " << x << endl;
    int n; cin >> n;
    return n;
}

void solve() {
    int n, k; cin >> n >> k;
    int hi = -1;
    for(int i = 1; i <= n; i++) {
        int val = ask(1,n * i);
        if(val == n) {
            hi = i;
        }
    }

    int res = -1;
    for(int m = hi; m / hi <= n / k; m += hi) {
        int cnt = 0, l = 1;
        for(int i = 0; i < k; i++) {
            if(l == n + 1) break;
            int x = ask(l,m);
            if(x == n + 1) break;
            cnt++;
            l = x + 1;
        }
        if(cnt == k && l == n + 1) res = m;
    }
    cout << "! " << res << endl;
    int ok; cin >> ok;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}