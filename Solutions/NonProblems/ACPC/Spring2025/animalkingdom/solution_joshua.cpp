#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a; cin >> a;
    
    if(a[0] <= 'm') {
        cout << "alpaca\n";
    } else {
        cout << "zebra\n";
    }

    return 0;
}
