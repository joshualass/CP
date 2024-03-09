#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int num; cin >> num;
    vector<int> v(3);
    int left = num - 3;
    for(int i = 2; i >= 0; i--) {
        int move = min(25,left);
        v[i] += move;
        left -= move;
    }
    for(int i = 0; i < 3; i++) {
        cout << (char) ('a' + v[i]);
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