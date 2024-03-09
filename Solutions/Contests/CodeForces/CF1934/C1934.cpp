#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int ask(int x, int y) {
    cout << "? " << x + 1 << " " << y + 1 << endl;
    int i; cin >> i;
    return i;
}

void solve() {
    int n, m; cin >> n >> m;
    int dist = ask(0,0);
    int x = min(dist,n-1), y = dist - x;
    int low = ask(x,y);
    int y1 = min(dist,m-1), x1 = dist - y1;
    int hi = ask(x1,y1);
    int x2 = x - low/2, y2 = y + low/2;
    int try1 = ask(x2,y2);
    if(try1 == 0) {
        cout << "! " << x2 + 1 << " " << y2 + 1<< endl;
    } else {
        cout << "! " << x1 + hi/2 + 1 << " " << y1 - hi/2 + 1 << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}