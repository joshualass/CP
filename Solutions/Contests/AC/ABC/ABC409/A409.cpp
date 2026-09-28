#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s, t; cin >> s >> t;
    int ok = 0;
    for(int i = 0; i < n; i++) ok |= s[i] == t[i] && s[i] == 'o';

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}
