#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int cnt = 0;
    for(char c : s) {
        if(c == '+') {
            cnt++;
        } else {
            cnt--;
        }
    }
    cout << abs(cnt) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}