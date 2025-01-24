#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, t; cin >> s >> t;
    int res = 1;
    for(int i = 0; i < 4; i++) {
        if(s[i] != t[i]) res *= 2;
    }

    cout << res << '\n';

    return 0;
}