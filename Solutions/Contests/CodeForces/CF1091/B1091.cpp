#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ll sx = 0, sy = 0;
    for(int i = 0; i < n * 2; i++) {
        int x, y; cin >> x >> y;
        sx += x;
        sy += y;
    }

    cout << sx / n << " " << sy / n << '\n';

    return 0;
}
