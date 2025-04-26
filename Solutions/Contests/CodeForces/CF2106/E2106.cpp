#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        m[a[i]] = i;
    }
    for(int i = 0; i < q; i++) {
        int l, r, x; cin >> l >> r >> x;
        l--, r--;
        int targ = m[x];
        if(targ < l || targ > r) {
            cout << "-1 ";
            continue;
        }
        int c = 0, d = 0;
        int lt = 0, rt = 0;
        while(l <= r) {
            int m = (l + r) / 2;

            if(a[m] == x) break;

            int ngr = targ > m;
            int gr = a[m] < x;

            if(ngr) {
                rt++;
            } else {
                lt++;
            }

            if(ngr != gr) {
                if(gr) {
                    c++;
                } else {
                    d++;
                }
            }
            if(ngr) {
                l = m + 1;
            } else {
                r = m - 1;
            }

        }
        int ue = x - 1, oe = n - x;
        if(rt > ue || lt > oe) {
            cout << "-1 ";
            continue;
        }
        // cout << "c : " << c << " d : " << d << " ue : " << ue << " oe : " << oe << '\n';
        cout << c + d + max(c, d) - min(c, d) << " ";
    }
    cout << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}