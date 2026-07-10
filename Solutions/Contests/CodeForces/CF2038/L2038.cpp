#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << 1000 / 6 << " " << 1000 % 6 << endl;

    // cout << 166 * 7 << endl;

    int n; cin >> n;

    cout << n / 6 * 7 + (n % 6 ? n % 6 + 1 : 0) << '\n';


    return 0;
}
