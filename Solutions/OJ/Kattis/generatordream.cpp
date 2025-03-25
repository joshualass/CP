#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int p; cin >> p;
    string b; cin >> b;

    int par = b[0] - '0';
    int l = par, r = p - 1;
    if((r - par) & 1) r--;

    while(l != r) {
        int m = (l + r) / 2;
        if((m - par) & 1) m--;

        int ok = 0;
        int c = m;
        for(int i = 0; i < b.size(); i++) {
            int targ_p = b[i] - '0';
            if((c & 1) != targ_p) {
                if(targ_p) {
                    ok = 1; 
                } else {
                    ok = -1;
                }
                break;
            }
            c = c * 2 % p;
        }

        if(ok == 0) {
            l = m;
            r = m;
        } else if(ok == -1) {
            r = m - 2;
        } else {
            l = m + 2;
        }
    }

    cout << l << '\n';

    return 0;
}