#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x]++;
    }

    // if(k == 0 && a[1] == n) {
    //     k++;
    //     n += 2;
    //     a.push_back(0);
    //     a.push_back(0);
    //     a[1] += 2;
    // }

    auto check = [&](int ops) -> int {
        if((ops - n) % 2) ops--;

        int splits = (ops - n) / 2;
        int clears = (n + ops) / 2;
        int avail_ops = max(0, k + ops - 1 - n);
        auto b = a;

        int init_splits = splits;

        // cout << "ops : " << ops << " splits : " << splits << " clears : " << clears << " avail_ops : " << avail_ops << endl;

        for(int i = n; i >= 0; i--) {
            if(k + init_splits <= i && i <= k + ops - 1) {
                // cout << "add avail i : "<< i << endl;    
                avail_ops++;
            }
            int sub = min(avail_ops, b[i]);
            // cout << "i : " << i << " avail : " << avail_ops << " sub : " << sub << endl;
            avail_ops -= sub;
            b[i] -= sub;
            assert(b[i] >= 0);
            if(splits < b[i]) return 0;
            splits -= b[i];
            b[(i + 1) / 2] += b[i] * 2;
        }

        // assert(splits == 0);
        return 1;

    };

    int l = n, r = n * 3;
    while(l != r) {
        int m = (l + r) / 2;
        if(check(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}