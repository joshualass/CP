#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    int res = max(0, min(30, t - 360)) + max(0, min(15, t - 570)) + max(0, t - 645);

    // if(t <= )


    cout << res << '\n';

    return 0;
}
