#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c; cin >> a >> b >> c;
    
    cout << (c == 0 ? a + b : a * b) << '\n';

    return 0;
}
