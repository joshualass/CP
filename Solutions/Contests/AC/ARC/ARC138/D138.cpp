#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;

    if(k == n) {
        if(n == 1) {
            cout << "Yes\n0 1\n";
        } else {
            cout << "No\n";
        }
    } else if(k % 2 == 0) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        int cycle_bits = k + 1;
        int long_cycle_bits = n - cycle_bits;
        int curr = 0;
        for(int i = 1; i <= 1 << long_cycle_bits; i++) {
            for(int j = 1; j < 1 << cycle_bits; j++) {
                cout << curr << " ";
                curr ^= ((1 << cycle_bits) - 1) - (1 << __builtin_ctz(j));
            }
            cout << curr << " ";
            curr ^= (1 << (cycle_bits + __builtin_ctz(i))) + ((1 << (cycle_bits - 2)) - 1);
        }
        cout << '\n';
    }

    return 0;
}