#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n), b(m);
    for(auto &x : a) cin >> x;
    for(auto &y : b) cin >> y;

    for(int i = 0; i < n - m + 1; i++) {
        for(int j = 0; j < n - m + 1; j++) {
            int ok = 1;
            for(int k = 0; k < m; k++) {
                for(int l = 0; l < m; l++) {
                    if(a[i+k][j+l] != b[k][l]) ok = 0;
                }
            }
            if(ok) {
                cout << i + 1 << " " << j + 1 << '\n';
                return 0;
            }
        }
    }

    return 0;
}