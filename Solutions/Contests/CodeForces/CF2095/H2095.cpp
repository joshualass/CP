#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> a = {
        "CODEFORCES",
        "EYE",
        "TESTING",
        "SYSTEM",
        "APRIL",
        "FOOLS",
        "YOU",
        "READ",
        "POORLY",
        "GET",
        "EYEGLASSES"
    };

    int x; cin >> x;
    cout << a[x - 1] << '\n';

    return 0;
}
