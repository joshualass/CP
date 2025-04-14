#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c; cin >> a >> b >> c;
    cout << (a * b == c || a * c == b || b * c == a ? "Yes" : "No") << '\n';

    return 0;
}
