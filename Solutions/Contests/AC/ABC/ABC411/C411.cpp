#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    int res = 0;
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        x--;
        int cnt = 0;
        int pc = 0;
        for(int j = max(0, x - 1); j <= min(n - 1, x + 1); j++) {
            if(a[j] != pc) {
                pc = a[j];
                cnt += a[j];
            }
        }

        res -= cnt;
        a[x] ^= 1;
        cnt = 0, pc = 0;
        for(int j = max(0, x - 1); j <= min(n - 1, x + 1); j++) {
            if(a[j] != pc) {
                pc = a[j];
                cnt += a[j];
            }
        }

        res += cnt;

        cout << res << '\n';

    }

    return 0;
}
