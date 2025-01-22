#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    //construct grid depending on parity of row
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i & 1) {
                cout << (1LL << (i + j - 1)) << " ";
            } else {
                cout << 0 << " ";
            }
        }
        cout << endl;
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll k; cin >> k;
        int x = 0, y = 0;
        cout << (x + 1) << " " << (y + 1) << endl;
        for(int j = 0; j < (n - 1) * 2; j++) {
            if((k >> j) & 1) {
                if(x & 1) { //partiy differs
                    y++;
                } else { //parity same
                    x++;
                }
            } else {
                if(x & 1) { //partiy differs
                    x++;
                } else { //parity same
                    y++;
                }
            }
            cout << (x + 1) << " " << (y + 1) << endl;
        }
    }

    return 0;
}