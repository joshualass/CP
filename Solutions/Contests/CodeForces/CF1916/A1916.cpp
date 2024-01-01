#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n, k; cin >> n >> k;
    bool ok = 1;
    int num = 2023;
    for(int i = 0; i < n; i++) {
        int val; cin >> val;
        if(num % val != 0) ok = 0;
        num /= val;
    }
    if(!ok) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for(int i = 1; i < k; i++) {
        cout << "1 ";
    }
    cout << num << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}