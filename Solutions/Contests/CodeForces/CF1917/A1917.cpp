#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    int cnt = 0;
    bool zerofound = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num < 0) cnt++;
        if(num == 0) {
            zerofound = 1;
        }
    }
    if(zerofound) {
        cout << "0\n";
    } else {
        if(cnt & 1) {
            cout << "0\n";
        } else {
            cout << "1\n1 0\n";
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}