#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << 10000.0 / 6.0 + 10000.0 / 10.0 + 10000.0 / 15.0 - 10000.0 / (60.0) - 10000.0 / (90.0) - 10000.0 / (150.0) + 10000.0 / (900.0) << '\n';

    int n; cin >> n;
    cout << "6 10 15 ";
    n -= 3;
    int i = 16;
    while(n) {
        if(i % 10 == 0 || i % 6 == 0 || i % 15 == 0) {
            cout << i << " ";
            n--;
        }
        i++;
    }

    cout << '\n';

    return 0;
}