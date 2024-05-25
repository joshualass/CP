#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // freopen(".in","r",stdin);
    freopen("g.in","w",stdout);

    cout << "1\n";
    int n = 200000;
    cout << n << '\n';
    for(int i = 0; i < n; i++) {
        cout << 1 << " \n"[i == n - 1];
    }

    return 0;
}