#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if((i + j) & 1) {
                if(a[i][j] == 'A') {
                    a[i][j] = 'C';
                } else {
                    a[i][j] = 'A';
                }
            } else {
                if(a[i][j] == 'B') {
                    a[i][j] = 'D';
                } else {
                    a[i][j] = 'B';
                }
            }
        }
    }

    for(auto &x : a) cout << x << '\n';

    return 0;
}
