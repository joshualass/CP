#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l; cin >> n >> l;
    vector<array<int,2>> a(l);

    for(int i = 0; i < n; i++) {
        int d, r, g; cin >> d >> r >> g;
        a[d] = {r, g};
    }

    int time = 0;
    for(int i = 0; i < l; i++) {
        if(a[i] != array<int,2>{0, 0}) {
            int wait = max(0, a[i][0] - time % (a[i][0] + a[i][1]));
            time += wait;
        }
        time++;
    }

    cout << time << '\n';

    return 0;
}
