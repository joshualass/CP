#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int res = INT_MAX;
    int prev; cin >> prev;
    for(int i = 1; i < n; i++) {
        int next; cin >> next;
        res = min(res,max(prev,next));
        prev = next;
    }   
    cout << res - 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}