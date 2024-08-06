#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

bool insertBasis(vector<int> &basis, int x) {
    for(int bit = basis.size() - 1; bit >= 0; bit--) {
        if(x & (1 << bit)) {
            if(basis[bit] == -1) {
                basis[bit] = x;
                return 1;
            } else {
                x ^= basis[bit];
            }
        }
    }
    return 0;
}

void solve() {
    int k, m; cin >> k >> m;
    vector<int> basis(k, -1);

    int cnt = 0;

    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        cnt += insertBasis(basis, num);
    }

    cout << (1 << (k - cnt)) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}