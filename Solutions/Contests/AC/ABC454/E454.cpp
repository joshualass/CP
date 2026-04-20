#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, a, b; cin >> n >> a >> b;
    if((n & 1) || (a + b) % 2 == 0) {
        cout << "No\n";
        return;
    }

    string res = "";

    for(int col = 1; col + 1 < b; col += 2) {
        res.append(string(n - 1, 'D'));
        res.push_back('R');
        res.append(string(n - 1, 'U'));
        res.push_back('R');
    }

    for(int row = 1; row + 1 < a; row += 2) {
        res.push_back('R');
        res.push_back('D');
        res.push_back('L');
        res.push_back('D');
    }

    if(b & 1) {
        res.append("RD");
    } else {
        res.append("DR");
    }

    for(int row = a; row + 2 <= n; row += 2) {
        res.append("DLDR");
    }
    res.push_back('R');

    for(int col = b; col + 2 <= n; col += 2) {
        res.append(string(n - 1, 'U'));
        res.push_back('R');
        res.append(string(n - 1, 'D'));
        res.push_back('R');
    }

    res.pop_back();

    cout << "Yes\n";
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}