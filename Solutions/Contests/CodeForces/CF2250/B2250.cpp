#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    if(k == n - 1) {
        cout << "-1\n";
        return;
    }
    string s = "";
    s.append(string((k + 1) / 2 + 1, '0'));
    s.append(string(k / 2 + 1, '1'));

    int f = 1;
    while(sz(s) < n) {
        if(f) {
            s = "1" + s;
            f = 0;
        } else {
            s.push_back(((s.back() - '0') ^ 1) + '0');
        }
    }

    cout << s << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}