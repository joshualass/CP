#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    if(n == 1) {
        cout << "1\n1\n";
    } else {
        cout << n / 2 << '\n';
        for(int i = 2; i <= n; i += 2) cout << i << " ";
        cout << '\n';
    }

    return 0;
}
