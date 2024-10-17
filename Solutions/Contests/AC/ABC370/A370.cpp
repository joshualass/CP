#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b; cin >> a >> b;

    if((a + b) % 2 == 0) {
        cout << "Invalid\n";
    } else if(a) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}