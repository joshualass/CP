#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

void solve() {

    int a, b, c, d; cin >> a >> b >> c >> d;
    int ok = a + 1 == b && c + 1 == d;
    if(ok == 0) {
        cout << "-1\n";
        return;
    }
    int w = c - a;
    if(w <= 1) {
        cout << "-1\n";
        return;
    }
    int col = (a - 1) % w;
    ok = ok && col != w - 1;
    if(ok) {
        cout << 50000 << " " << w << '\n';
    } else {
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}