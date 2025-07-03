#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c; cin >> a >> b >> c;
    cout << (c ? a * b : a + b) << '\n';

    return 0;
}