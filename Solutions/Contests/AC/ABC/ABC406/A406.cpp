#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c, d; cin >> a >> b >> c >> d;
    if(c * 60 + d < a * 60 + b) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
