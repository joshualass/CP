#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
j - i = A_i + A_j
j - A_j = A_i + i

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ll res = 0;
    map<ll,ll> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        res += m[i - x];
        m[i + x]++;
    }

    cout << res << '\n';

    return 0;
}
