#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, b, a; cin >> n >> b >> a;
    int ma = a;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int e; cin >> e;
        if(a < ma && e && b) {
            b--;
            a++;
        } else if(a) {
            a--;
        } else if(b) {
            b--;
        } else {
            break;
        }
        res++;
    }

    cout << res << '\n';

    return 0;
}
