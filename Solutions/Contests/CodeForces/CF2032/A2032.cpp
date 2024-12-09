#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int sum = 0, zerocnt = 0;
    for(int i = 0; i < n * 2; i++) {
        int x; cin >> x;
        sum += x;
        if(x == 0) zerocnt++;
    }
    while(sum > n) sum -= 2;
    cout << (sum & 1) << " " << min(sum,zerocnt) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}