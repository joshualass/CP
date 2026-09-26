#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> b(n + 1);
    int swapper = 0;
    int who = a[0];
    for(int i = 1; i < n; i++) {
        int bi = i + 1;
        if(swapper) {
            assert(who > a[i - 1]);
            if(a[i] < a[i - 1]) {
                b[bi] = b[bi - 2];
                swapper = 1;
                who = a[i - 1];
            } else if(a[i] < who) {
                b[bi] = b[bi - 1] + 2;
                swapper = 1;
                who = who;
            } else {
                swapper = 0;
                b[bi] = b[bi - 1] + 2;
                who = a[i];
            }
        } else {
            if(a[i] < who) {
                b[bi] = b[bi - 2];
                swapper = 1;
                who = a[i - 1];
            } else {
                swapper = 0;
                b[bi] = b[bi - 1] + 2;
                who = a[i];
            }
        }
    }

    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        cout << b[r] << '\n';
    }

    return 0;
}
