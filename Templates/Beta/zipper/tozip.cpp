#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll i, o, t, j, l, s, z; cin >> i >> o >> t >> j >> l >> s >> z;
    ll res = i / 2 * 2 + o + j / 2 * 2 + l / 2 * 2;
    
    if(i && j && l) { //check if i, j and l pieces exists so we can consider the i, j, l combination
        res = max(res, (i - 1) / 2 * 2 + o + (j - 1) / 2 * 2 + (l - 1) / 2 * 2 + 3);
    }

    cout << res << '\n';

    return 0;
}