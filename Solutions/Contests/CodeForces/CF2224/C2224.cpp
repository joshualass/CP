#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string a, b; cin >> a >> b;

    int ok = 1;

    auto check = [&](string &s) -> void {
        int cur = 0;
        for(char c : s) {
            if(c == '(') {
                cur++;
            } else {
                cur--;
            }
            if(cur < 0) ok = 0;
        }
        if(cur) ok = 0;
    };

    int p = 0;

    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]) {
            a[i] = '(';
            b[i] = ')';
            if(p) {
                swap(a[i], b[i]);
            }
            p ^= 1;
        }
    }

    check(a);
    check(b);

    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}