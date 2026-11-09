#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    int res = 0;
    for(int i = 0; i < 100000; i++) {
        // int time = n * i;
        // int latest = (time + 9) / 10 * 10;
        // int next_latest = (time + n + 9) / 10 * 10;

        // if(next_latest != latest) {
        //     res = max(res, latest - time);
        // }
        int time = 10 * i;
        int latest = time / n * n;
        res = max(res, time - latest);
    }

    cout << res << '\n';

    return 0;
}
