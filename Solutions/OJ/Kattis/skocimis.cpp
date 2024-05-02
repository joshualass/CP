#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c; cin >> a >> b >> c;
    cout << max(c - b, b - a) - 1 << '\n';

    return 0;
}