#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    cout << ((int)(s[0] - '0') * (s[2] - '0')) << '\n';

    return 0;
}