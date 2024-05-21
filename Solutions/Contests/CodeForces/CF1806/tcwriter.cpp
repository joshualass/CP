#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // freopen(".in","r",stdin);
    freopen("E.in","w",stdout);

    int n = 100000, q = 1;
    cout << n << " " << q << '\n';

    for(int i = 0; i < n; i++) {
        cout << i + 1 << " \n"[i == n - 1];
    }
    for(int i = 1; i < n; i++) {
        cout << i << " \n"[i == n - 1];
    }
    cout << n << " " << n << '\n';

    return 0;
}