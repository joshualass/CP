#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // freopen(".in","r",stdin);
    freopen("ccp.in","w",stdout);

    int n = 100000;
    cout << n << '\n';
    for(int i = 0; i < n; i++) {
        cout << 2 << " \n"[i == n - 1];
    }

    return 0;
}