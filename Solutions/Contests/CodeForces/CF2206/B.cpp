#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> p(n);
    vector<int> leaf(n, 1);
    for(int i = 1; i < n; i++) {
        int a; cin >> a;
        a--;
        p[i] = a;
        leaf[a] = 0;
    }

    int l = 0, r = n - 1;
    vector<int> res(n);
    while(l != r) {
        int m = (l + r) / 2;
        res.assign(n, 0);
        for(int i = n - 1; i >= 0; i--) {
            if(leaf[i]) {
                if(i <= m) {
                    res[i] = 1;
                } else {
                    res[i] = -1;
                }
            }
            if(i) {
                if(res[i] > 0) res[p[i]]++;
                if(res[i] < 0) res[p[i]]--;
            }
        }
        if(res[0] >= 0) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l + 1 << '\n';

    return 0;
}
