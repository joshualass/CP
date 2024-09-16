#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    for(int i = 0; i < (n + 4) / 5; i++) {
        cout << 'a';
    }
    for(int i = 0; i < (n + 3) / 5; i++) {
        cout << 'e';
    }
    for(int i = 0; i < (n + 2) / 5; i++) {
        cout << 'i';
    }
    for(int i = 0; i < (n + 1) / 5; i++) {
        cout << 'o';
    }
    for(int i = 0; i < (n) / 5; i++) {
        cout << 'u';
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