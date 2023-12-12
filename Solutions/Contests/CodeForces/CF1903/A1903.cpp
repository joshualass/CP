#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    int prev = -1;
    bool flag = 1;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num < prev) {
            flag = 0;
        }
        prev = num;
    }
    if(flag || k >= 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}