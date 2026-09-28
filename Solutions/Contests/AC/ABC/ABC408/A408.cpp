#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s; cin >> n >> s;
    int p = 0;
    int bad = 0;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x - p > s) bad = 1;
        p = x;
    }

    cout << (bad ? "No" : "Yes") << '\n';

    return 0;
}
